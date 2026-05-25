# Hardware Setup

This guide covers the mechanical and electrical setup required to assemble the Smart IoT Prosthetic Hand prototype.

## Required Components

- Arduino UNO
- 5 x SG90 servo motors
- 5 x IR analog proximity sensors
- Breadboard and jumper wires
- 7.4V battery pack or 5V regulated DC supply for servo power
- 3D-printed prosthetic hand body
- 5 x nylon actuation threads
- 10 kΩ potentiometer (optional for manual calibration)

## Mechanical Assembly

1. Mount each servo inside the prosthetic palm housing.
2. Route a nylon thread from each servo horn to the corresponding finger segment.
3. Ensure the string path remains smooth and free of binding.
4. Secure the servo cable to avoid tension transfer to the electronics.
5. Verify that each finger returns to the rest position when the servo is relaxed.

## Electrical Wiring

- Servo signal wires connect to digital pins `D3`, `D5`, `D6`, `D9`, and `D10`.
- Servo power rails connect to a dedicated 5V supply with common ground to Arduino.
- Each IR sensor output connects to analog pins `A0` through `A4`.
- Each IR sensor VCC connects to `5V` and GND to Arduino ground.
- Optionally, a potentiometer can be connected to `A5` as a calibration reference.

## Power Considerations

- Use a separate 5V supply for servo motors to avoid brownouts on the Arduino.
- Connect all grounds together to maintain stable analog readings.
- If using a battery pack, verify the voltage output under load before powering servos.

## Assembly Notes

- Avoid powering the servos directly from the Arduino 5V regulator when multiple servos are active.
- Route sensor wiring away from high-current servo cables to reduce noise.
- Add decoupling capacitors on the supply rail if the system shows jitter.

## Testing the Wiring

1. Load `testing/servo_test.ino` in Arduino IDE.
2. Confirm each servo sweeps smoothly without jerk.
3. Load `testing/sensor_test.ino`.
4. Read raw sensor values in Serial Monitor to verify each IR channel responds.
