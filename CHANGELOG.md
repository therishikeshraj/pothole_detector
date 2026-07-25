# Changelog

All notable changes to the **ROAD SHIELD – Smart Pothole Detection System** project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## [1.0.0] - 2026-07-25

### Added
- Real-time 3-axis accelerometer sampling using MPU6050 sensor via I2C bus.
- Z-axis threshold anomaly detection algorithm ($upperLimit = 15.0 \, m/s^2$, $lowerLimit = 5.0 \, m/s^2$).
- Automatic telemetry dispatch to Firebase Realtime Database over WiFi.
- Modular telemetry schema containing X, Y, Z accelerations, timestamp, and geolocation metrics.
- Professional open-source documentation suite (`README.md`, `INSTALLATION.md`, `PROJECT_STRUCTURE.md`, `CONTRIBUTING.md`, `SECURITY.md`, `CODE_OF_CONDUCT.md`).
- Circuit pinout guide and high-resolution architecture diagrams.
- Standard MIT License and `.gitignore` file.

### Security
- Sanitized hardcoded WiFi credentials and Firebase API keys with configurable placeholder definitions.

## [Unreleased / Future Scope]
- Integration of NEO-6M GPS hardware module for dynamic NMEA coordinate retrieval.
- Edge AI / TensorFlow Lite gesture model integration for road surface profiling.
- Native Flutter mobile application for road maintenance authority dashboards.
- Offline telemetry buffering using SPIFFS / EEPROM cache.
