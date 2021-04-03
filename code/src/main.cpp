#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <avr/pgmspace.h>

#define LED_DDR DDRK
#define LED_PORT PORTK
#define BUTTON_DDR DDRA
#define BUTTON_PORT PORTA
#define BUTTON_PIN PINA
#define FIRST_BUTTON_PIN_NUMBER 0
#define SECOND_BUTTON_PIN_NUMBER 2
#define LED_QUANTITY 8
#define DELAY_IN_MS 1050

#define USART_BAUDRATE 9600   
#define BAUD_PRESCALE (((F_CPU / (USART_BAUDRATE * 16L))) - 1)

const PROGMEM unsigned char ALGORITHMS[2][8] = {
  { 1 << 7, 1 << 5, 1 << 3, 1 << 1, 1 << 6, 1 << 4, 1 << 2, 1 << 0 },
  { 1 << 0, 1 << 1, 1 << 2, 1 << 3, 1 << 4, 1 << 5, 1 << 6, 1 << 7 }
};

volatile char receivedData;

ISR(USART0_RX_vect) {
  receivedData = UDR0;
}

void init() {
  LED_DDR = 0xFF;
  LED_PORT = 0x00;

  BUTTON_DDR = 0x00;
  BUTTON_PORT = 1 << FIRST_BUTTON_PIN_NUMBER | 1 << SECOND_BUTTON_PIN_NUMBER;

  UBRR0 = BAUD_PRESCALE;
  UCSR0B = ((1 << TXEN0) | (1 << RXEN0) | (1 << RXCIE0));
}

void sendByteToUSART(uint8_t u8Data) {
  while ((UCSR0A & (1 << UDRE0)) == 0);
  UDR0 = u8Data;
}

int main(void) {
  sei();
  init();
  while (1) {

    if (!(BUTTON_PIN & 1 << FIRST_BUTTON_PIN_NUMBER)) {
      while (!(BUTTON_PIN & 1 << FIRST_BUTTON_PIN_NUMBER)) {} // wait until the button is released to send data just once
      sendByteToUSART('0');
    }

    if (!(BUTTON_PIN & 1 << SECOND_BUTTON_PIN_NUMBER)) {
      while (!(BUTTON_PIN & 1 << SECOND_BUTTON_PIN_NUMBER)) {}
      sendByteToUSART('1');
    }

    if (receivedData > -1) {
      int algorithmNumber = receivedData - '0';
      if (algorithmNumber == 0 || algorithmNumber == 1) {
        for (int i = 0; i < LED_QUANTITY; i++) {
          LED_PORT = pgm_read_byte(&ALGORITHMS[algorithmNumber][i]);
          _delay_ms(DELAY_IN_MS);
        }
        LED_PORT = 0x00;
        receivedData = -1;
      }
    }

  }
}