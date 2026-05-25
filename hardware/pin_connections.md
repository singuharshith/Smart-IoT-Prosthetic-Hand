# Pin Connections

## Servo Connections

| Finger | Servo Pin | Arduino Pin |
| --- | --- | --- |
| Thumb | Servo 1 | D3 |
| Index | Servo 2 | D5 |
| Middle | Servo 3 | D6 |
| Ring | Servo 4 | D9 |
| Little | Servo 5 | D10 |

## Sensor Connections

| Sensor | Analog Channel | Arduino Pin |
| --- | --- | --- |
| Thumb IR | CH1 | A0 |
| Index IR | CH2 | A1 |
| Middle IR | CH3 | A2 |
| Ring IR | CH4 | A3 |
| Little IR | CH5 | A4 |

## Power Wiring

- Servos: separate 5V power supply
- Common ground: connect servo ground, sensor ground, and Arduino ground together
- Sensor VCC: 5V from Arduino
- Sensor GND: Arduino GND

## Optional Calibration Potentiometer

- Potentiometer center pin to A5
- One side to 5V, other side to GND

## Notes

- Keep servo signal wires separate from power rails to reduce interference.
- Use heat shrink or header connectors for reliable servo connections.
- Verify the dedicated servo supply is capable of handling peak current from all 5 servos.
