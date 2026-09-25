

# 🐍 Embedded Snake Game - ATmega32

A fully customized, bare-metal **Snake Game** implemented on the **ATmega32** microcontroller using C and Layered Software Architecture. The system utilizes an **8x8 / 16x16 LED Dot Matrix** driven by **74HC595 / 74LS595 Shift Registers**, featuring a custom Real-Time Cooperative Scheduler and serial input control.

---

## 🎬 Project Demo
[Watch Demo](https://drive.google.com/file/d/1OlHiWpVTC9NQdPLk8mPbD8QYBAuPUd-P/view?usp=drive_link)
---

##  Key Features

* **Layered Software Architecture:** Clean isolation between Hardware drivers (`MCAL`, `HAL`), Application logic (`APP`), and Common libraries (`LIB`)[cite: 1, 2].
* **Shift Register Multiplexing:** Utilizes **74HC595 / 74LS595 Shift Registers** to drive the LED Dot Matrix while conserving microcontroller I/O pins.
* **Cooperative Task Scheduler:** Custom non-blocking OS scheduler for accurate timing of game ticks, matrix scanning, and USART inputs.
* **Flicker-Free Display Rendering:** Optimized multiplexing routines for smooth gameplay visualization.
* **Dynamic Snake Logic:** Real-time direction handling, food spawning, wall boundary handling, and self-collision detection.

---

## 📁 Directory Structure

The repository matches the standard embedded C project layers[cite: 1, 2]:

```text
SNAKE_GAME/
├── APP/                    # Application Layer & Game Logic
│   ├── main.c              # Main Entry Point
│   ├── SNAKE_config.h      # Game Settings (Grid Size, Initial Speed)
│   ├── SNAKE_interface.h   # Application Public APIs
│   ├── SNAKE_private.h     # Internal Macros & Game Structures
│   └── SNAKE_program.c     # Snake Game State Machine & Rules
│
├── HAL/                    # Hardware Abstraction Layer
│   ├── DOT_MATRIX/         # LED Matrix Display Driver
│   └── SHIFT_REG/          # 74HC595 / 74LS595 Shift Register Driver
│
├── MCAL/                   # Microcontroller Abstraction Layer
│   ├── ADC/                # Analog-to-Digital Converter Driver
│   ├── DIO/                # GPIO Input/Output Driver
│   ├── Interrupt/          # External Interrupt Handlers
│   ├── Scheduler/          # Cooperative Task Scheduler Driver
│   ├── TIMER_0/            # Timer0 Driver (Tick Generator)
│   └── USART/              # Serial Communication Driver
│
└── LIB/                    # Utility Libraries
    ├── BIT_MATH.h          # Bit Manipulation Macros
    └── STD.h               # Standard Embedded Data Types

```

---

## 🛠️ Hardware Requirements

* **Microcontroller:** ATmega32 (Target Clock: 8MHz / 16MHz)
* **Display Output:** LED Dot Matrix Display (8x8 or 16x16)
* **Shift Registers:** 74HC595 / 74LS595 (Serial-In Parallel-Out)
* **Input Interfaces:** USART Serial Controller / Push Buttons
* **Programmer:** USBasp / AVR ISP Programmer

---

## 🔌 Pin Mapping

| Peripheral | Target Pin (ATmega32) | Function |
| --- | --- | --- |
| **74LS595 Data** | PORTA Pin 0 | DS (Serial Data) |
| **74LS595 Shift Clock** | PORTA Pin 1 | SH_CP (Shift Clock) |
| **74LS595 Latch Clock** | PORTA Pin 2 | ST_CP (Storage/Latch Clock) |
| **USART Receiver** | PORTD Pin 0 | RXD (Direction Control) |
| **USART Transmitter** | PORTD Pin 1 | TXD (Status / Debugging) |

---

## ⚙️ How to Build and Run

1. Clone this repository to your local machine:
```bash
git clone https://github.com/mazenmohammed156200/Snake-Game-ATmega32.git

```


2. Open **Eclipse IDE for C/C++ Developers** (with AVR Plugin).
3. Import the project (`File -> Import -> Existing Projects into Workspace`).
4. Build the project (`Ctrl + B`).
5. Flash the generated `.hex` binary (found in the `Debug/` folder) to your ATmega32 using `AVRDUDE` or your programmer interface.

---

## 👥 Authors & Contributors

This project was developed by:

* **Mazen Mohammed Said** - *Embedded Systems Developer* - https://github.com/mazenmohammed156200
* **Mohamed Hesham Mohamed** - *Embedded Systems Developer* - https://github.com/mohamed2612

---


