# 📁 Project Structure & Taxonomy

This document outlines the directory structure and file responsibilities within the **ROAD SHIELD** repository.

```text
pothole_detector/
├── README.md                 # Primary project overview, hardware specs, setup, & badges
├── LICENSE                   # Open-source MIT License terms
├── .gitignore                # IDE and build artifact exclusion rules
├── libraries.txt             # Manifest of required Arduino IDE dependencies
├── main_code.ino             # Main ESP32 firmware sketch (sanitized & fully commented)
├── CHANGELOG.md              # Historical version tracking and milestone releases
│
├── docs/                     # Detailed project documentation suite
│   ├── INSTALLATION.md       # Step-by-step flashing and environment setup guide
│   ├── PROJECT_STRUCTURE.md  # File taxonomy and structural overview (this file)
│   ├── CONTRIBUTING.md       # Open-source contribution guidelines & PR process
│   ├── CODE_OF_CONDUCT.md    # Community standards & Contributor Covenant v2.1
│   └── SECURITY.md           # Secret protection policy & vulnerability handling
│
├── images/                   # High-resolution visual media & telemetry screenshots
│   ├── hardware_setup.png    # ESP32 + MPU6050 physical breadboard assembly
│   ├── esp32_mpu6050.png     # Close-up wiring view
│   ├── serial_monitor.png    # Live Serial Monitor output logs
│   ├── serial_plotter.png    # 3-axis accelerometer waveform plots
│   ├── firebase_dashboard.png# Firebase Realtime Database JSON payload tree
│   └── system_architecture.png# End-to-end telemetry system architecture diagram
│
└── circuit/                  # Hardware schematics & wiring specifications
    ├── circuit_diagram.png   # High-resolution circuit schematic diagram
    └── pinout_guide.md       # Comprehensive hardware pinout specification
```

---

## 🔍 Directory Descriptions

### Root Folder (`/`)
- Contains primary project descriptors, firmware entry points, dependency listings, and license files required by GitHub open-source standards.

### Documentation Folder (`/docs`)
- Houses comprehensive technical documentation covering environment setup, open-source governance, security disclosures, and project maintenance rules.

### Visual Assets (`/images`)
- High-quality diagrams, hardware photographs, and console output screenshots embedded across project READMEs and technical documentation.

### Circuit Specs (`/circuit`)
- Dedicated hardware wiring blueprints, I2C pinout tables, and voltage regulation notes for developers reproducing the physical system.
