# AVR microcontroller lab 2

## Task

1. Для зв’язку клієнтської програми з Proteus необхідно встановити пару віртуальних COM-портів.
2. Запуск роботи алгоритмів зі світлодіодами виконується шляхом натиску відповідних кнопок на клієнтській формі.
3. При натисканні кнопок на МК запускаються відповідні алгоритми блимання іконок на клієнтській формі.

| Кнопки   | Світлодіоди | Затримка | Алгоритм |
| -------- | ----------- | -------- | -------- |
| PA0, PA2 | port-K      | 1,05 сек | 6, 1     |

### Опис алгоритмів

Лінійка з 8-ми одноколірних світлодіодів. При натисканні кнопки світлодіоди починають почергово блимати через один від 7-виводу порту до 1, а потім далі від 6 до 0.  
P0← P2←P4←P6←P1←P3←P5←P7

Лінійка з 8-ми одноколірних світлодіодів. При натисканні
кнопки світлодіоди почергово блимають від 0-виводу порту до 7.  
P0→P1→P2→P3→P4→P5→P6→P7

## Getting Started

### Prerequisites

- Install [VS Code](https://code.visualstudio.com/Download)
- Install [PlatformIO](https://platformio.org/install/ide?install=vscode)
- Install [Proteus](https://www.labcenter.com/)
- Install [Python 3.8+](https://www.python.org/downloads/release/python-382/)

### Installing

- Clone repository into your system

```
git clone https://github.com/Ravenen/microcontroller_lab_1.git
```

- Activate Python virtual environment

  - Windows

  ```
  GUI\venv\Scripts\activate
  ```

  - Unix

  ```
  source GUI/venv/Scripts/activate
  ```

- Install requirements from `requirements.txt`

```
pip install -r GUI/requirements.txt
```

### Executing program

- Build a project in `code` folder via PlatformIO builder
- Run the `GUI/app.py` file
- Open Proteus project, configure COMPIM with COM port and speed, and run the simulation

## Authors

[Vitaliy Pavliyk (@ravenen)](https://github.com/Ravenen)
