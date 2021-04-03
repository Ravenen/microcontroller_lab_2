import time
from typing import Dict, Any, List, Union

import serial
from PyQt5 import QtWidgets

from constants import *
from design import design
from misc import serial_ports
from model.listener import Listener


class COMUI(QtWidgets.QMainWindow, design.Ui_MainWindow):
    def __init__(self):
        super().__init__()
        self.setupUi(self)
        self.port: Union[serial.Serial, None] = None
        self.listener = None
        self.init_elements()
        self.algorithms: Dict[Any, List[QtWidgets.QLabel]] = {
            str(ALGORITHM_FIRST): [self.led7, self.led5, self.led3, self.led1, self.led6, self.led4, self.led2,
                                   self.led0],
            str(ALGORITHM_SECOND): [self.led0, self.led1, self.led2, self.led3, self.led4, self.led5, self.led6,
                                    self.led7]}

    def init_elements(self):
        self.comComboBox.addItems(serial_ports())
        self.speedComboBox.addItems(SPEEDS)
        self.openComButton.clicked.connect(self.connect)
        self.algorithmFirstButton.clicked.connect(self.send_algorithm_first)
        self.algorithmSecondButton.clicked.connect(self.send_algorithm_second)

    def connect(self):
        try:
            self.port = serial.Serial(self.comComboBox.currentText(), int(self.speedComboBox.currentText()),
                                      parity=serial.PARITY_NONE,
                                      stopbits=serial.STOPBITS_ONE,
                                      bytesize=serial.EIGHTBITS)
            self.openComButton.setStyleSheet(f"background-color: {COLOR_GREEN};")
            self.openComButton.setText('Підімкнено')
            self.listen_port()
        except Exception as e:
            print(e)

    def listen_port(self):
        self.listener = Listener(self.port, self.receive_message)
        self.listener.start()

    def send_algorithm_first(self):
        self.send_message(ALGORITHM_FIRST)

    def send_algorithm_second(self):
        self.send_message(ALGORITHM_SECOND)

    def send_message(self, message):
        if self.port:
            self.port.write(str(message).encode("utf-8"))

    def receive_message(self, message):
        print(message.decode("utf-8"))
        algorithm = self.algorithms.get(message.decode("utf-8"), None)
        if algorithm:
            self.run_algorithm(algorithm)

    def run_algorithm(self, algorithm: List[QtWidgets.QLabel]):
        for led in algorithm:
            led.setStyleSheet(f"background-color: {COLOR_GREEN};")
            time.sleep(DELAY_IN_MS)
            led.setStyleSheet(f"background-color: {COLOR_BLUE};")
            time.sleep(0.005)
