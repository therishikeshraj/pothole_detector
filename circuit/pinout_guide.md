# 🔌 Hardware Pinout & Wiring Specifications

This guide details the physical hardware interconnections for assembling the **ROAD SHIELD** pothole detection system using an ESP32 microcontroller and an MPU6050 6-axis accelerometer/gyroscope.

---

## 📌 Wiring Table

| ESP32 Dev Module Pin | MPU6050 Sensor Pin | Signal Function | Operating Voltage |
| :--- | :--- | :--- | :--- |
| **3V3** | `VCC` | Power Supply | 3.3V DC |
| **GND** | `GND` | Common Ground | 0V |
| **GPIO 21 (I2C SDA)** | `SDA` | Serial Data Line | 3.3V Logic |
| **GPIO 22 (I2C SCL)** | `SCL` | Serial Clock Line | 3.3V Logic |

---

## ⚡ Technical Specifications & Electrical Notes

### 1. I2C Bus Communication
- **Address**: `0x68` (Default when MPU6050 `AD0` pin is left floating or connected to GND). If `AD0` is pulled HIGH (3.3V), address changes to `0x69`.
- **Clock Speed**: Standard Mode (100 kHz) or Fast Mode (400 kHz).
- **Pull-up Resistors**: The MPU6050 breakout module includes onboard $4.7\,k\Omega$ pull-up resistors on both SDA and SCL lines to 3.3V. External pull-ups are not required when using standard breakout boards.

### 2. Sensor Orientation
- For accurate Z-axis vertical acceleration measurements, mount the MPU6050 module **flat on the vehicle chassis / breadboard** with the component side facing upwards.
- In stationary standard orientation:
  - $X \approx 0.0 \, m/s^2$
  - $Y \approx 0.0 \, m/s^2$
  - $Z \approx 9.81 \, m/s^2$ (Gravity acceleration force)

---

## 📐 Circuit Diagram Schematic

Refer to [`circuit/circuit_diagram.png`](circuit_diagram.png) for high-resolution visual wiring reference.
