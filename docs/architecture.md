# System Architecture

## High-Level Overview

The Smart IoT Prosthetic Hand firmware is organized into modular layers to separate concerns, enable future expansion, and streamline diagnostics.

### Key Layers

- `main.ino` — System coordinator, startup flow, handshake sequence, and runtime loop.
- `config.h` — Global constants, pin assignments, thresholds, and calibration storage indices.
- `sensor_manager.*` — Sensor acquisition, moving average filtering, and raw-to-normalized conversion.
- `servo_controller.*` — Servo initialization, safe motion interpolation, and per-finger actuation.
- `gesture_mapper.*` — Gesture logic, threshold mapping, and combined finger gestures.
- `calibration.*` — Calibration routines, EEPROM persistence, and live threshold tuning.
- `filters.*` — Utility filters used for smoothing analog sensor data and servo ramping.
- `utilities.*` — Support functions, debug logging, serial command processing, and helper macros.

## Data Flow

```text
[IR Sensors] -> [Sensor Manager] -> [Moving Average Filter] -> [Gesture Mapper] -> [Servo Controller] -> [Prosthetic Fingers]
```

### Startup and Initialization

1. `main.ino` initializes serial communication and diagnostic flags.
2. `config.h` loads compile-time constants and EEPROM indices.
3. `SensorManager::begin()` initializes sensor pins and enables sampling.
4. `ServoController::initialize()` attaches servos and performs a safe homing routine.
5. `CalibrationManager::load()` reads stored calibration values from EEPROM.
6. The system enters the primary control loop and begins real-time sensing.

## Real-Time Control Loop

The firmware executes the following tasks in each loop iteration:

- read all analog sensor values
- apply moving average filtering for each channel
- map sensor readings to normalized degrees using calibration values
- determine gestures and finger target positions
- execute smooth interpolation for each servo
- log diagnostics periodically to serial monitor

## Modularity and Extensibility

The firmware structure supports future expansion in these areas:

- EMG sensor reading and classifier input
- wireless Bluetooth command interface
- WiFi telemetry and OTA control
- mobile app control layer
- AI gesture prediction layer using embedded or external inference

## Safety and Reliability

Safety checks are implemented at every stage:

- servo movement is clamped to `MIN_SERVO_ANGLE` and `MAX_SERVO_ANGLE`
- sensor values outside expected range trigger fail-safe logs
- calibration data is validated before use
- startup homing prevents abrupt servo motion
- debug mode enables step-by-step verification via Serial
