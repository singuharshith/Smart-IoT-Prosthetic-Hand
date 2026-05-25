# Demo Description

This demo document describes the key user interactions and expected behavior for the Smart IoT Prosthetic Hand prototype.

## Demo Scenario

1. Power on the Arduino UNO and servo power supply.
2. Open the Arduino Serial Monitor at `115200` baud.
3. Observe the startup self-test sequence and calibration status.
4. The hand performs a brief servo homing routine to confirm motion range.
5. Place the five IR sensors in front of the corresponding control surfaces.
6. Move a control surface closer to the IR sensor to drive the corresponding finger.
7. The hand should respond with smooth, gradual finger movement.
8. Press `C` in the Serial Monitor to run a recalibration sequence if needed.

## Expected Behavior

- Finger motion is smooth, not abrupt.
- Each finger maps independently to its sensor input.
- Calibration values are loaded and applied automatically.
- Serial output displays sensor readings, target angles, and status messages.

## Demonstration Goals

- Show stable sensor filtering and smooth actuation.
- Highlight the modular firmware architecture.
- Demonstrate safety features such as angle clamping and startup diagnostics.
- Signal future expansion paths including EMG and wireless control.
