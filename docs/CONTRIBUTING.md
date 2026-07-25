# 🤝 Contributing to ROAD SHIELD

Thank you for your interest in contributing to **ROAD SHIELD – Smart Pothole Detection System**! We welcome contributions from developers of all skill levels, embedded systems enthusiasts, and open-source advocates.

---

## 🛠️ How to Contribute

### 1. Reporting Bugs
- Search existing [GitHub Issues](https://github.com/therishikeshraj/pothole_detector/issues) to verify if the issue has already been reported.
- If not, open a new issue using a descriptive title. Include:
  - ESP32 Core / Arduino IDE version
  - Hardware schematic variations (if any)
  - Complete error output or Serial Monitor logs

### 2. Requesting Features
- We encourage proposals for additional sensors (e.g., GPS modules, cellular modems), algorithm refinements, or cloud dashboard integrations.
- Open a feature request issue describing the rationale and proposed architecture.

### 3. Submitting Pull Requests (PRs)
1. **Fork** the repository to your own GitHub account.
2. **Clone** your fork locally:
   ```bash
   git clone https://github.com/YOUR-USERNAME/pothole_detector.git
   ```
3. Create a feature branch:
   ```bash
   git checkout -b feature/amazing-feature
   ```
4. Commit your changes with concise, informative commit messages.
5. Push to your branch:
   ```bash
   git push origin feature/amazing-feature
   ```
6. Open a **Pull Request** against our `main` branch.

---

## 🔐 Code Guidelines

- **Never commit real WiFi credentials or Firebase API keys**. Use placeholder constants (`YOUR_WIFI_SSID`, `YOUR_FIREBASE_API_KEY`).
- Maintain clear inline code comments for hardware register access and data transformations.
- Test firmware build compatibility in Arduino IDE prior to opening a PR.
