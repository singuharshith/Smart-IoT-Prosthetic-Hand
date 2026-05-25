# Bluetooth Module

## Concept

A Bluetooth module would add wireless control and status reporting capabilities. A mobile or PC app could send gesture commands, request calibration, or monitor sensor values remotely.

## Proposed Architecture

- Integrate an HC-05/HC-06 or BLE module with serial UART communication.
- Define a command protocol for gesture selection and calibration triggers.
- Mirror current sensor and servo state over Bluetooth for remote debugging.
- Add a wireless fallback mode in `utilities.cpp`.

## Benefits

- Removes the need for direct USB connection during demonstrations.
- Enables mobile app control and telemetry.
- Supports remote tuning and firmware testing.
