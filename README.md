# Dual-Axis Tilt Direction Tracking Mechanism

An open-loop physical direction-tracking prototype built with an Arduino, two **SW-520D** ball-contact tilt sensors, and a micro servo motor. The system detects directional tilt (left/right) of a breadboard platform and mirrors that orientation by steering the servo to preset angles.

---

## Hardware Components
* 1x Arduino microcontroller (Uno, Nano, etc.)
* 1x Micro Servo (SG90)
* 2x SW-520D Ball Tilt Switches
* Breadboard and jumper wires

---

## Working Principle & Physical Alignment
The SW-520D sensors are mounted onto independent breadboard columns to prevent internal short circuits. Mechanically, they are arranged symmetrically in a slight outward "V-configuration."

The microcontroller enables internal pull-up resistors (`INPUT_PULLUP`). When the platform rests horizontally, both sensors remain in an open-circuit state (`HIGH`). When tilted past the physical threshold, the internal gold-plated balls roll onto the contact leads, pulling the pin to ground (`LOW`). The firmware translates this logic into servo positions (45° for left, 135° for right, and 90° for neutral).

### Tilt Angle vs. Sensitivity Correlation
Through empirical testing on this hardware setup, the following mechanical behavior was verified:
* **Increasing the outward tilt angle of the sensors directly increases the system's sensitivity to tilt deviations.**
* As the baseline angle increases, the internal metal balls rest closer to the electrical contact threshold. Consequently, even a slight angular displacement of the platform triggers immediate contact closure, resulting in faster and more responsive servo actuation.
* An optimal mounting angle exists between excessive chatter/bounce (too flat) and delayed response (too vertical), which was tuned experimentally.

---

## Circuit Connections

| Component | Pin | Arduino Pin | Logic / State |
| :--- | :--- | :--- | :--- |
| **Left Sensor (SW-520D)** | Lead 1 / Lead 2 | D2 / GND | `LOW` when tilted left |
| **Right Sensor (SW-520D)** | Lead 1 / Lead 2 | D3 / GND | `LOW` when tilted right |
| **Servo Motor** | Signal (Orange/Yellow) | D9 (PWM) | Controlled via `Servo.h` |
| **Servo Motor** | VCC / GND | 5V / GND | Power supply |

---

## Planned Enhancements
* Non-blocking, `millis()`-based software debouncing to handle contact bounce without using blocking `delay()` calls.
* Integration of the **SW-18020P** vibration switch via an external hardware interrupt (`attachInterrupt()`) for emergency shutdown or tap-based mode toggling.
* Implementation of an S-curve or linear interpolation algorithm to replace step-based servo motion with smooth, continuous trajectory transitions.
