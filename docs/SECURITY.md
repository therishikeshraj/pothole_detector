# 🔒 Security Policy

## Supported Versions

We recommend keeping your firmware and dependent Arduino libraries updated to the latest stable versions.

| Version | Supported          |
| ------- | ------------------ |
| 1.0.x   | :white_check_mark: |
| < 1.0.0 | :x:                |

---

## 🛡️ Secret & Credential Protection Guidelines

Embedded IoT devices connected to cloud backends must adhere to strict credential security practices:

### 1. Hardcoded Credentials Prevention
- **NEVER** commit real WiFi SSIDs, WPA passwords, Firebase Web API Keys, or Database URLs to a public GitHub repository.
- Use sanitized placeholder values in source files (`YOUR_WIFI_SSID`, `YOUR_FIREBASE_API_KEY`).

### 2. Best Practice: Local Header Configuration
We recommend decoupling secrets into an untracked local header file (`secrets.h`):

```cpp
// secrets.h (Add to .gitignore)
#define SECRET_WIFI_SSID     "MyHomeWiFi"
#define SECRET_WIFI_PASS     "SuperSecretPassword"
#define SECRET_FIREBASE_KEY  "AIzaSy..."
#define SECRET_FIREBASE_URL  "https://my-db.firebaseio.com"
```

In your main sketch:
```cpp
#include "secrets.h"
#define WIFI_SSID     SECRET_WIFI_SSID
#define WIFI_PASSWORD SECRET_WIFI_PASS
#define API_KEY       SECRET_FIREBASE_KEY
#define DATABASE_URL  SECRET_FIREBASE_URL
```

---

## 🚨 Reporting a Vulnerability

If you discover a potential security vulnerability (e.g., exposed API keys, memory leaks, buffer overflows in I2C parsing), please **DO NOT** open a public issue.

Instead, please notify the lead maintainer directly via GitHub contact or email. We will investigate and patch the issue promptly.
