# 🛠️ Installation & Setup Guide

This document provides step-by-step instructions for assembling, configuring, and flashing the **ROAD SHIELD** firmware onto the ESP32 microcontroller.

---

## 📋 Prerequisites

Before proceeding, ensure you have the following software tools installed on your development machine:

1. **[Arduino IDE](https://www.arduino.cc/en/software)** (Version 2.0 or higher recommended)
2. **[CP210x USB to UART Bridge Driver](https://www.silabs.com/developers/usb-to-uart-bridge-vcp-drivers)** or **CH340 Driver** (depending on your ESP32 board's USB interface chip)
3. Active **WiFi network** (2.4 GHz frequency band; ESP32 does not support 5 GHz networks)
4. A **Firebase Account** with a configured Realtime Database instance

---

## ⚙️ Step 1: ESP32 Board Setup in Arduino IDE

1. Open **Arduino IDE**.
2. Navigate to `File` ➔ `Preferences` (`Ctrl + Comma`).
3. In the **Additional Boards Manager URLs** field, add the following URL:
   ```text
   https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json
   ```
4. Open the **Boards Manager** (`Tools` ➔ `Board` ➔ `Boards Manager...`).
5. Search for `esp32` by **Espressif Systems** and click **Install**.

---

## 📚 Step 2: Install Required Libraries

1. Open the **Library Manager** (`Tools` ➔ `Manage Libraries...` or `Ctrl + Shift + I`).
2. Search for and install:
   - **`Firebase ESP Client`** by *Mobizt* (Supports ESP32 & Realtime Database).
3. Verify built-in libraries:
   - `Wire.h` (Pre-installed with ESP32 board package)
   - `WiFi.h` (Pre-installed with ESP32 board package)

---

## 🔥 Step 3: Firebase Realtime Database Configuration

1. Visit the [Firebase Console](https://console.firebase.google.com/).
2. Create a new Firebase project (or select an existing one).
3. Build ➔ **Realtime Database** ➔ Click **Create Database**.
4. Choose your preferred location and set Security Rules to **Test Mode** (or configure Read/Write rules):
   ```json
   {
     "rules": {
       ".read": true,
       ".write": true
     }
   }
   ```
5. Obtain database URL from database home header (e.g., `https://your-app-default-rtdb.firebaseio.com`).
6. Navigate to **Project Settings** (`⚙️`) ➔ **Web API Key** to obtain your Firebase Web API Key.

---

## 🔌 Step 4: Hardware Assembly

Connect the **MPU6050 Accelerometer** module to the **ESP32** using standard jumper wires:

| ESP32 Pin | MPU6050 Pin | Description |
| :--- | :--- | :--- |
| **3V3** | `VCC` | 3.3V Power Line |
| **GND** | `GND` | Common Ground |
| **GPIO 21** | `SDA` | I2C Serial Data Line |
| **GPIO 22** | `SCL` | I2C Serial Clock Line |

---

## 🚀 Step 5: Flashing Code

1. Clone or download this repository.
2. Open [`main_code.ino`](../main_code.ino) in Arduino IDE.
3. Replace configuration placeholders in lines 14–17:
   ```cpp
   #define WIFI_SSID       "YOUR_WIFI_SSID"
   #define WIFI_PASSWORD   "YOUR_WIFI_PASSWORD"
   #define API_KEY         "YOUR_FIREBASE_API_KEY"
   #define DATABASE_URL    "YOUR_FIREBASE_DATABASE_URL"
   ```
4. Connect ESP32 to computer via USB cable.
5. Select Board: `Tools` ➔ `Board` ➔ `ESP32 Arduino` ➔ **ESP32 Dev Module**.
6. Select Port: `Tools` ➔ `Port` ➔ (e.g., `COM3` or `/dev/ttyUSB0`).
7. Click **Upload** (`Ctrl + U`).

---

## 🔍 Step 6: Verification

1. Open **Serial Monitor** (`Ctrl + Shift + M`) set to **115200 baud**.
2. Shake or tilt the sensor breadboard to trigger detection threshold ($Z > 15.0 \, m/s^2$ or $Z < 5.0 \, m/s^2$).
3. Confirm message `✅ Telemetry Successfully Synced to Firebase RTDB` appears on console.
