/**
 * ============================================================================
 * PROJECT   : ROAD SHIELD – Smart Pothole Detection System
 * FILE      : main_code.ino
 * AUTHOR    : Rishikesh Raj & Contributors
 * BOARD     : ESP32 Dev Module
 * SENSORS   : MPU6050 Accelerometer & Gyroscope (I2C)
 * DATABASE  : Firebase Realtime Database
 * LICENSE   : MIT License
 * ============================================================================
 * 
 * DESCRIPTION:
 * Real-time pothole detection system utilizing 3-axis accelerometer data from
 * the MPU6050 sensor. When vertical Z-axis acceleration exceeds defined safety
 * thresholds (bump/pothole event), telemetry payload (X, Y, Z, GPS Lat/Lng, Time)
 * is immediately dispatched to Firebase Realtime Database over WiFi.
 * 
 * HARDWARE CONNECTIONS:
 * ----------------------------------------------------------------------------
 *  ESP32 Pin     | MPU6050 Module Pin | Description
 * ----------------------------------------------------------------------------
 *  3V3           | VCC                | 3.3V Power Supply
 *  GND           | GND                | Common Ground
 *  GPIO 21 (SDA) | SDA                | I2C Data Line
 *  GPIO 22 (SCL) | SCL                | I2C Clock Line
 * ----------------------------------------------------------------------------
 */

#include <Wire.h>
#include <WiFi.h>
#include <Firebase_ESP_Client.h>
#include "esp_log.h"

// ============================================================================
// CONFIGURATION & CREDENTIAL PLACEHOLDERS
// Replace these placeholders with your actual network and Firebase credentials
// ============================================================================
#define WIFI_SSID       "YOUR_WIFI_SSID"
#define WIFI_PASSWORD   "YOUR_WIFI_PASSWORD"
#define API_KEY         "YOUR_FIREBASE_API_KEY"
#define DATABASE_URL    "YOUR_FIREBASE_DATABASE_URL"

// ============================================================================
// HARDWARE & SENSOR DEFINITIONS
// ============================================================================
const int MPU_addr = 0x68;  // I2C address of MPU6050

// Raw accelerometer readings
int16_t AcX, AcY, AcZ;

// Converted acceleration values in m/s²
float x_m_s2, y_m_s2, z_m_s2;

// Detection Thresholds (Z-axis acceleration in m/s²)
float upperLimit = 15.0;     // Severe upward spike / impact (m/s²)
float lowerLimit = 5.0;      // Sudden drop / free-fall into pothole (m/s²)

// ============================================================================
// GEOLOCATION TELEMETRY (Dummy coordinates for testing / modular expansion)
// ============================================================================
float latitude  = 12.9716;   // Default test latitude  (Bangalore, India)
float longitude = 77.5946;   // Default test longitude (Bangalore, India)

// ============================================================================
// FIREBASE CLIENT OBJECTS
// ============================================================================
FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;

// Timers
unsigned long potholeTime = 0;

// ============================================================================
// INITIALIZATION (SETUP)
// ============================================================================
void setup() {
  // Initialize Serial Interface for debugging
  Serial.begin(115200);
  
  // Disable low-level ESP-IDF debug log noise
  esp_log_level_set("*", ESP_LOG_NONE);

  // Initialize I2C Communication (SDA = GPIO 21, SCL = GPIO 22)
  Wire.begin(21, 22);

  // Wake up MPU6050 (Exit sleep mode by setting PWR_MGMT_1 register to 0)
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x6B);
  Wire.write(0);
  Wire.endTransmission(true);
  Serial.println("✅ MPU6050 Accelerometer Initialized");

  // Establish WiFi Connection
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("📡 Connecting to WiFi Network");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\n✅ WiFi Connected Successfully");
  Serial.print("🌐 Device IP Address: ");
  Serial.println(WiFi.localIP());

  // Firebase Realtime Database Configuration
  config.api_key = API_KEY;
  config.database_url = DATABASE_URL;
  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);
  Serial.println("🔥 Firebase Realtime Database Ready");

  // Serial Plotter Headers
  Serial.println("\n===== SERIAL PLOTTER FORMAT =====");
  Serial.println("X,Y,Z");
}

// ============================================================================
// MAIN LOOP
// ============================================================================
void loop() {
  // Request 14 bytes starting from ACCEL_XOUT_H register (0x3B)
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x3B);
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_addr, 14, true);

  if (Wire.available() == 14) {
    // Read raw 16-bit accelerometer outputs
    AcX = Wire.read() << 8 | Wire.read();
    AcY = Wire.read() << 8 | Wire.read();
    AcZ = Wire.read() << 8 | Wire.read();

    // Skip Temperature (2 bytes) and Gyroscope (6 bytes) registers
    for (int i = 0; i < 8; i++) {
      Wire.read();
    }

    // Convert raw values to m/s² (16384 LSB/g for +/-2g scale; 1g = 9.81 m/s²)
    x_m_s2 = (AcX / 16384.0) * 9.81;
    y_m_s2 = (AcY / 16384.0) * 9.81;
    z_m_s2 = (AcZ / 16384.0) * 9.81;

    // ------------------------------------------------------------------------
    // SERIAL PLOTTER OUTPUT FORMAT (CSV)
    // ------------------------------------------------------------------------
    Serial.print(x_m_s2);
    Serial.print(",");
    Serial.print(y_m_s2);
    Serial.print(",");
    Serial.println(z_m_s2);

    // ------------------------------------------------------------------------
    // SERIAL MONITOR CONSOLE FORMAT
    // ------------------------------------------------------------------------
    Serial.print("X: ");
    Serial.print(x_m_s2);
    Serial.print(" | Y: ");
    Serial.print(y_m_s2);
    Serial.print(" | Z: ");
    Serial.println(z_m_s2);

    // ------------------------------------------------------------------------
    // POTHOLE ANOMALY DETECTION LOGIC
    // Triggered when Z acceleration exceeds upper threshold or drops below lower limit
    // ------------------------------------------------------------------------
    if (z_m_s2 > upperLimit || z_m_s2 < lowerLimit) {
      potholeTime = millis() / 1000;  // System uptime in seconds

      Serial.println("\n===========================================");
      Serial.println("⚠️ POTHOLE / ROAD ANOMALY DETECTED!");
      Serial.print("⏱️ Time Uptime (sec): ");
      Serial.println(potholeTime);
      Serial.print("📍 Latitude         : ");
      Serial.println(latitude, 6);
      Serial.print("📍 Longitude        : ");
      Serial.println(longitude, 6);
      Serial.print("📊 Accel X (m/s²)   : ");
      Serial.println(x_m_s2);
      Serial.print("📊 Accel Y (m/s²)   : ");
      Serial.println(y_m_s2);
      Serial.print("📊 Accel Z (m/s²)   : ");
      Serial.println(z_m_s2);
      Serial.println("===========================================\n");

      // ----------------------------------------------------------------------
      // TELEMETRY UPLOAD TO FIREBASE REALTIME DATABASE
      // ----------------------------------------------------------------------
      if (Firebase.ready()) {
        Firebase.RTDB.setFloat(&fbdo, "/RoadShield/Pothole/X", x_m_s2);
        Firebase.RTDB.setFloat(&fbdo, "/RoadShield/Pothole/Y", y_m_s2);
        Firebase.RTDB.setFloat(&fbdo, "/RoadShield/Pothole/Z", z_m_s2);
        Firebase.RTDB.setFloat(&fbdo, "/RoadShield/Pothole/Latitude", latitude);
        Firebase.RTDB.setFloat(&fbdo, "/RoadShield/Pothole/Longitude", longitude);
        Firebase.RTDB.setInt(&fbdo, "/RoadShield/Pothole/TimeSec", potholeTime);

        Serial.println("✅ Telemetry Successfully Synced to Firebase RTDB");
      }
      delay(500); // Debounce delay after detection
    }
  } else {
    Serial.println("⚠️ MPU6050 Bus Read Error");
  }

  delay(200); // Sensor sampling rate (~5Hz)
}
