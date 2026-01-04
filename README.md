# 🥤 Smart Touchless Vending Machine

![Arduino](https://img.shields.io/badge/Platform-Arduino_Uno-blue?style=for-the-badge&logo=arduino)
![Language](https://img.shields.io/badge/Language-C%2B%2B-00599C?style=for-the-badge&logo=c%2B%2B)
![Status](https://img.shields.io/badge/Status-Prototype_Complete-success?style=for-the-badge)

> **Abstract:** This project demonstrates the design and implementation of a prototype automatic vending machine, focusing on the integration of electronic sensing and mechanical actuation. The system utilizes an Arduino Uno microcontroller to govern the interaction between input sensors and output devices. Distance measurement is achieved using an HC-SR04 ultrasonic sensor for non-contact user detection. Upon verifying a proximity threshold, the system triggers a servo motor to dispense the product.

---

## 📖 Introduction

The field of **Applied Electromechanics** focuses on the synergistic integration of mechanical systems, electrical systems, and computer control. Automatic vending machines represent a classic application of these principles, requiring a seamless interface between digital logic and physical motion to operate without human intervention.

The objective of this project is to construct a functional, sensor-based vending mechanism that eliminates the need for physical buttons, thereby reducing mechanical wear and improving hygiene through touchless operation.

### Key Subsystems
* 📡 **Sensing:** An ultrasonic transceiver (HC-SR04) operates on the principle of sonar to calculate distance based on the time-of-flight of sound waves.
* 🧠 **Processing & Indication:** The microcontroller processes sensor data to distinguish valid requests, communicating state via an I2C-interface LCD.
* 🦾 **Actuation:** A servo motor serves as the final control element, converting electrical signals into precise angular displacement.

---

## 🛠 Hardware Interface & Pin Mapping

The system architecture is built around the **ATmega328P-based Arduino Uno**. Below is the precise connection logic used in the circuit.

| Component | Pin Label | Arduino Pin | Function |
| :--- | :--- | :--- | :--- |
| **I2C LCD Display** | SDA | **A4** | I2C Data Line |
| | SCL | **A5** | I2C Clock Line |
| | VCC | 5V | Power Supply |
| | GND | GND | Ground |
| **Ultrasonic Sensor** | Trig | **D7** | Input Signal (Sends pulse) |
| | Echo | **D8** | Output Signal (Receives echo) |
| | VCC | 5V | Power Supply |
| | GND | GND | Ground |
| **Servo Motor** | Signal | **D3** | PWM Control Signal |
| | VCC | 5V | Power Supply |
| | GND | GND | Ground |

---

## ⚙️ Technical Methodology

### 1. Distance Calculation Algorithm
The core functionality relies on the precise measurement of distance using the **Time-of-Flight (ToF)** principle.

The distance calculation is initiated by a $10\mu s$ trigger pulse sent to the sensor's `Trig` pin. The sensor emits a burst of eight ultrasonic cycles at $40\text{ kHz}$. When these waves encounter an obstacle, they are reflected back, and the `Echo` pin outputs a HIGH signal equal to the travel duration.

#### Derivation of the Formula
The distance is calculated using the fundamental kinematic equation $d = v \times t$. However, two adjustments are required:

1.  **Round Trip Adjustment:** The time returned is for the trip there and back, so it must be divided by 2.
2.  **Speed of Sound Constant ($0.0343$):** Converting the speed of sound ($343\text{ m/s}$) to $\text{cm}/\mu s$.

$$\text{Speed} \approx 0.0343 \text{ cm}/\mu s$$

Substituting these values yields the final formula implemented in the software:

$$Distance (\text{cm}) = \frac{\text{duration}(\mu s) \times 0.0343}{2}$$

### 2. Implementation Justifications

> **I2C Bus Usage**
> The LCD module utilizes the I2C protocol to minimize pin usage. On the Arduino Uno, the hardware I2C interface is physically located on pins **A4 (SDA)** and **A5 (SCL)**.

> **Sensor Timing**
> The HC-SR04 relies on microsecond-level timing. The Trigger pin receives a $10\mu s$ HIGH pulse to initiate ranging, while the Echo pin outputs a pulse width proportional to the distance.

> **PWM Actuation**
> The servo motor position is controlled via Pulse Width Modulation (PWM) on **Digital Pin 3**. The library generates specific duty cycles (typically $1ms$ to $2ms$) to map the motor angle between $0^{\circ}$ and $180^{\circ}$.

---

## ✅ Conclusion

The "Smart Touchless Vending Machine" project successfully demonstrates the practical application of electromechanical principles controlled by embedded logic.

Experimental results confirm that the system reliably detects user presence within the programmed threshold of **$\le 5.0 \text{ cm}$**. The integration of the I2C LCD module provided effective real-time feedback, and the use of PWM allowed for precise control of the dispensing arm. This project bridges the gap between theoretical circuit analysis and physical application, proving the viability of non-contact sensing systems in public hygiene-focused applications.

---

## 🚀 Future Scope

While the current prototype serves as a proof-of-concept, the following enhancements could enable commercial viability:

* **Multi-Product Selection:** utilizing a matrix of motors to dispense multiple product types.
* **Payment Integration:** Interfacing with RFID modules (RC522) or coin acceptors for conditional dispensing.
* **Feedback Control Loop:** Adding IR break-beam sensors to confirm physical product delivery.
* **IoT Monitoring:** Using an ESP32 to transmit stock levels to a central server for real-time inventory tracking.

---
