# Custom-PCB-Smart-Calculator-Arduino-Nano-
# Custom PCB Smart Calculator (Arduino Nano)

Final Aseembly: ![IMG_4860](https://github.com/user-attachments/assets/829d0453-60f6-4ee0-befb-94178365e2e7)

## 📌 Project Overview
Driven by a desire to experience the full hardware development lifecycle, I deliberately transitioned from a multi-board prototyping plan to engineer a **unified single-board PCB**. This project integrates an Arduino Nano, an I2C OLED display, a 4x4 matrix keypad, and an active buzzer into a compact, standalone smart calculator.

* **Development Period:** Feb 2026 – Mar 2026
* **Key Skills:** PCB Routing (EasyEDA), Hardware Soldering, C++ (Arduino Firmware), I2C Communication

---

## 🛠️ Hardware Engineering

### The Challenge: From Digital CAD to Physical Reality
As my first full hardware build, the core challenge was bridging the gap between digital CAD (EasyEDA) and physical component reality. I manually sourced components, matched physical footprints to CAD libraries, and routed the board to ensure electrical integrity without bridging. 

*(Note: During the initial PCB design phase, I encountered a pin-mapping mismatch, which I successfully mitigated by utilizing wire-wrapping (jumper wires) on the back of the board—a hands-on lesson in the critical importance of rigorous datasheet review before manufacturing.)*

### Bill of Materials (BOM) - DigiKey Sourcing
| # | Part Number | Description | Qty |
|---|---|---|---|
| 1 | 1050-1001-ND | ARDUINO NANO ATMEGA328 EVAL BRD | 1 |
| 2 | A26425-ND | CONN RCPT 15POS 0.1 GOLD PCB | 2 |
| 3 | 1528-3844-ND | SWITCH KEYPAD 16KEY NON-ILLUM | 1 |
| 4 | 1738-DFR0650-ND | DFR0650 GRAPHIC DISPLAY OLED WHITE 0.96" | 1 |
| 5 | 668-AI-2429-TWT-5V-R-ND | BUZZER PIEZO 5V 24MM TH | 1 |
| 6 | 399-9871-1-ND | CAP CER 0.1UF 50V X7R RADIAL | 10 |
| 7 | P11212-ND | CAP ALUM 10UF 20% 25V RADIAL TH | 2 |

*See `Hardware_Design` folder for Schematic PDF and Gerber files.*

---

## 💻 Firmware & Software Design

The firmware was written in C++ using the Arduino IDE. It manages matrix keypad scanning and handles the SSD1306 OLED display via robust I2C communication.

### Key Features:
* **Dynamic UI Scaling:** The OLED display automatically adjusts text size based on the length of the user input (e.g., switches to smaller text if the input exceeds 6 or 10 characters).
* **Robust Edge-Case Handling:** Implemented logic to catch critical arithmetic errors, such as displaying `Err:Div0` and pausing the system when a division by zero is attempted.
* **Auditory Feedback:** Integrated active buzzer responses for distinct keypress confirmations.

*See `Firmware` folder for the `.ino` source code.*
