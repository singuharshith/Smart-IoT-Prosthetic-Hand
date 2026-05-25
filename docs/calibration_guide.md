# Calibration Guide

Accurate sensor calibration is critical for reliable prosthetic finger motion. This guide explains how to tune the system and store settings in EEPROM.

## Why Calibration Matters

IR sensor outputs vary with ambient lighting, sensor placement, and finger mechanics. Calibration enables:

- consistent motion mapping across trials
- sensor threshold adaptation to environmental changes
- reliable gesture detection
- stable finger behavior even when sensors drift

## Calibration Workflow

1. Power the board and open Serial Monitor at `115200` baud.
2. The firmware announces startup messages and calibration status.
3. Press `C` in the Serial Monitor to initiate calibration mode.
4. Follow prompts to set each finger's rest and extension values.
5. The system stores minimum and maximum readings in EEPROM.
6. The firmware uses these values to normalize each sensor channel.

## Calibration Procedure

### Step 1: Rest Position

- Place each finger in a relaxed or neutral position.
- Record sensor values for the rest position.
- Ensure the finger is not under tension or fully extended.

### Step 2: Extension Position

- Move each finger to the intended extension position.
- Record the maximum sensor response.
- Verify movement is smooth and repeatable.

### Step 3: Store Values

- The firmware writes calibration values to EEPROM automatically.
- Calibration values survive power cycles and reboot.

### Step 4: Validate

- Run the main firmware and observe the response curves.
- Compare sensor readings against expected target angles.
- If needed, repeat calibration after mechanical adjustments.

## EEPROM Management

- Calibration data is saved as a structured block in EEPROM.
- The system validates values before use.
- If EEPROM contains invalid or uninitialized data, default calibration is applied.

## Advanced Tuning

- Use the potentiometer on `A5` to perform manual adjustments in the field.
- Tune the `MOVING_AVERAGE_WINDOW` constant in `config.h` if sensor noise is high.
- Adjust `GESTURE_THRESHOLD` values for more aggressive or conservative finger mapping.

## Troubleshooting

- If a finger appears jittery, check the servo power supply and wiring.
- If the sensor reading is flat, verify the IR sensor orientation and distance.
- If only one channel fails, swap the sensor cable and retest with `sensor_test.ino`.
