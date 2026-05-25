# Smart IoT Prosthetic Hand

[![Project Status](https://img.shields.io/badge/status-prototype-blue)](https://github.com/)
[![License](https://img.shields.io/badge/license-MIT-green)](LICENSE)
[![Platform](https://img.shields.io/badge/platform-Arduino%20IDE-orange)](#)

## Project Overview

Smart IoT Prosthetic Hand is a hardware-focused robotics prototype built with Arduino Embedded C/C++ and designed as an assistive technology prototype for intuitive finger movement control. The system combines sensor-driven real-time motion, modular firmware design, and accessible calibration workflows to simulate natural hand movements using 5 servo-driven fingers.

This repository showcases a professional engineering-grade embedded systems project with detailed architecture, hardware documentation, calibration procedures, and future-ready expansion planning.

## Features

- 5-finger prosthetic hand control with individual servo actuation
- Real-time IR sensor-based fingertip motion mapping
- Moving average filter for sensor stabilization
- Smooth servo interpolation for gradual finger movement
- EEPROM-backed calibration and gesture threshold storage
- Modular firmware architecture with sensor, servo, gesture, filter, and utility layers
- Serial diagnostics and debug mode for rapid hardware validation
- Comprehensive hardware wiring and setup documentation
- Prepared for future integration with EMG, Bluetooth, WiFi, and AI gesture prediction

## Hardware Requirements

| Component | Description |
| --- | --- |
| Arduino UNO | Main microcontroller board |
| 5 x SG90 Servo Motors | Finger actuator motors |
| 5 x IR Analog Sensors | Finger position and proximity sensing |
| Breadboard & Jumper Wires | Power and signal distribution |
| 5 x Nylon Threads | Prosthetic finger tendon actuation |
| 3D-printed hand body | Mechanical finger structure |
| 7.4V battery pack or 5V regulated supply | Servo power source |
| 10 kΩ potentiometer | Calibration reference (optional) |

## Software Requirements

- Arduino IDE 1.8.x or 2.x
- Arduino AVR Boards package
- Standard Arduino libraries: `Servo.h`, `Wire.h`, `EEPROM.h`
- PC serial monitor for debugging

## Folder Structure

```text
Smart-IoT-Prosthetic-Hand/
├── README.md
├── LICENSE
├── .gitignore
├── docs/
│   ├── architecture.md
│   ├── hardware_setup.md
│   ├── calibration_guide.md
│   └── future_scope.md
├── hardware/
│   ├── circuit_diagram.png
│   ├── pin_connections.md
│   └── components_list.md
├── images/
│   ├── prototype.jpg
│   ├── setup.jpg
│   └── demo.jpg
├── src/
│   ├── main.ino
│   ├── config.h
│   ├── sensor_manager.h
│   ├── sensor_manager.cpp
│   ├── servo_controller.h
│   ├── servo_controller.cpp
│   ├── gesture_mapper.h
│   ├── gesture_mapper.cpp
│   ├── calibration.h
│   ├── calibration.cpp
│   ├── filters.h
│   ├── filters.cpp
│   ├── utilities.h
│   └── utilities.cpp
├── testing/
│   ├── sensor_test.ino
│   ├── servo_test.ino
│   └── calibration_test.ino
├── demo/
│   └── demo_description.md
└── future_modules/
    ├── emg_integration.md
    ├── bluetooth_module.md
    └── ai_prediction_module.md
```

## Circuit Explanation

The prosthetic hand uses a single Arduino UNO to read 5 analog IR sensors and drive 5 servo motors. Each sensor channel provides real-time distance readings that map directly to a corresponding servo position. A separate power supply is recommended for the servos to avoid voltage dips from the Arduino's onboard regulator.

### Working Principle

1. Each IR sensor monitors a user gesture or finger movement surrogate.
2. The MCU reads all sensor channels continuously and applies a moving average filter.
3. Filtered sensor values are compared against programmable thresholds.
4. Each finger servo is commanded using smooth interpolation to the target angle.
5. Calibration values are stored in EEPROM for power-cycle persistence.

## Installation

1. Clone or download the repository to your local machine.
2. Open `src/main.ino` in Arduino IDE.
3. Ensure the Arduino AVR board support package is installed.
4. Confirm wiring according to `hardware/pin_connections.md`.
5. Upload the firmware to Arduino UNO.

## Upload Instructions

1. Connect Arduino UNO to your PC via USB.
2. Select `Tools > Board > Arduino Uno`.
3. Select the correct `Tools > Port`.
4. Click `Upload`.
5. Open `Tools > Serial Monitor` at `115200` baud for startup diagnostics.

## Calibration Process

1. Power the system and open Serial Monitor.
2. Watch startup diagnostics, then follow prompts to begin calibration.
3. Place each finger in rest and maximum extension positions.
4. The firmware stores minimum and maximum sensor readings in EEPROM.
5. Calibration can be repeated any time by sending `C` over Serial.

## Demo

See `demo/demo_description.md` for how the hand behaves during a hardware demo. The system is designed to demonstrate smooth finger motion, reliable sensor mapping, and robust calibration.

## Screenshots

![Prototype](images/prototype.jpg)
![Setup](images/setup.jpg)
![Demo](images/demo.jpg)

## Future Scope

This repository includes dedicated modules and documentation for future hardware and software upgrades such as EMG signal integration, wireless control, mobile app connectivity, and AI-driven gesture prediction.

## Author

Developed as a research-driven prototype combining embedded systems, robotics, and IoT innovation. Ideal for robotics hackathons, embedded design portfolios, and assistive technology demonstrations.

## GitHub Topics

`Arduino` `Embedded` `Robotics` `IoT` `Prosthetics` `AssistiveTechnology` `Servo` `SensorFusion` `Firmware`

## License

This project is published under the MIT License. See `LICENSE` for details.
