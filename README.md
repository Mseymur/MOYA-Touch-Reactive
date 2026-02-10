# MOYA (Genwave) 🌊

![TouchDesigner](https://img.shields.io/badge/TouchDesigner-2022.3%2B-black?style=for-the-badge)
![Max](https://img.shields.io/badge/Max-8-000000?style=for-the-badge&logo=max&logoColor=white)
![Arduino](https://img.shields.io/badge/Arduino-IDE-00979D?style=for-the-badge&logo=arduino&logoColor=white)
![Platform](https://img.shields.io/badge/Platform-Installation-lightgrey?style=for-the-badge)

**MOYA** (also known as **Genwave**) is a site-specific interactive wall designed for a club night at Helmut List Halle. It serves as a social icebreaker, transforming a staircase entry into a collaborative, interactive experience rather than a passive queue.

> **Note:** This installation bridges physical touch with generative visuals using a combination of capacitive sensing, Max/MSP signal processing, and TouchDesigner.

---

## ✨ Features

*   **Six Touch Points:** Three points per staircase that map touch signals to motion, color, and patterns.
*   **Collaborative Interaction:** Visuals from the left and right staircases synchronize and merge when both groups interact simultaneously.
*   **Real-time Feedback:** Instant touch responsiveness with clear "cause-and-effect" visual mapping.
*   **Generative Visuals:** A dynamic system that evolves based on user input, ensuring no two moments look exactly the same.

## 🛠️ Tech Stack

*   **Visuals:** TouchDesigner (Real-time generative visuals)
*   **Signal Processing:** Max/MSP (Data smoothing, state machines)
*   **Hardware Control:** Arduino (Capacitive sensing)
*   **Connectivity:** Wi-Fi / UDP

## 📂 Structure

*   **[Arduino_ReceiveFromTouchBoard_CreateWifi.ino/](Arduino_ReceiveFromTouchBoard_CreateWifi.ino/)** - Arduino sketch for setting up Wi-Fi and reading touch data.
*   **[Arduino_ReceiveFromTouchBoard_SendUDP/](Arduino_ReceiveFromTouchBoard_SendUDP/)** - Arduino sketch for sending touch data via UDP.
*   **[GenWave_Transactor.maxpat](GenWave_Transactor.maxpat)** - Max patch for processing raw sensor data and smoothing signals.
*   **[MOYA Project.toe](MOYA%20Project.toe)** - Main TouchDesigner project file for the visual output.

## 🚀 Getting Started

### Prerequisites

*   Arduino Board + Conductive Pads
*   Max 8 (or later)
*   TouchDesigner
*   Wi-Fi Network (for UDP communication)

### Installation & Usage

1.  **Hardware:** 
    *   Upload the appropriate sketch to your Arduino board.
    *   Ensure conductive pads are connected and the device is on the correct network.
2.  **Signal Processing:** 
    *   Open `GenWave_Transactor.maxpat` in Max.
    *   Verify that UDP packets are being received from the Arduino.
3.  **Visuals:** 
    *   Open `MOYA Project.toe` in TouchDesigner.
    *   The visuals should react to the processed data coming from Max.

*Important: Ensure all devices are on the same local network to minimize latency.*

## 👥 The Team

Created in 2 months (2025).

*   **Seymur Mammadov**
*   **Jakob Schnurrer**

## 📄 License

[License](license)

---

*[Learn more about the project details here.](https://mseymur.framer.website/projects/genwave)*
