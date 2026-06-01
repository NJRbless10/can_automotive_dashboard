# CAN-Based Automotive Dashboard System

A real-time **CAN (Controller Area Network) based Automotive Dashboard** project developed using **Embedded C** and **PIC Microcontroller**.
The system simulates communication between automotive Electronic Control Units (ECUs) using the CAN protocol to monitor vehicle parameters like speed and gear position.

---

# 📌 Project Overview

Modern vehicles use the **CAN protocol** for communication between different ECUs.

This project demonstrates:

* CAN Bus communication
* Real-time sensor data transmission
* Automotive dashboard simulation
* Embedded system design using PIC microcontroller

The dashboard receives and displays vehicle-related data such as:

* Vehicle Speed
* Gear Position
* Engine Parameters
* Indicator Status

---

# 🚗 Objective

To design a simple automotive dashboard system where:

* Sensor ECU reads vehicle parameters
* Data is transmitted using CAN protocol
* Dashboard ECU receives and processes data
* Information can be displayed on LCD/UART

---

# 🛠 Technologies Used

* **Language:** Embedded C
* **Microcontroller:** PIC18 Series
* **Protocol:** CAN (Controller Area Network)
* **Compiler:** MPLAB XC8
* **IDE:** MPLAB X IDE

---

# 📂 Project Structure

```text id="6rjwrx"
CAN-car_model1.X/
│
├── adc.c / adc.h                 # ADC configuration and sensor reading
├── can.c / can.h                 # CAN protocol implementation
├── clcd.c / clcd.h               # Character LCD driver
├── digital_keypad.c / .h         # Keypad handling
├── ecu1_main.c                   # Main application
├── ecu1_sensor.c                 # Sensor ECU logic
├── ecu1sensor.h                  # ECU sensor declarations
├── uart.c / uart.h               # UART communication
├── msg_id.h                      # CAN message IDs
├── Makefile
└── nbproject/                    # MPLAB project files
```

---

# 🌐 About CAN Protocol

CAN (Controller Area Network) is widely used in automotive systems for reliable communication between ECUs.

### Features of CAN

* Multi-master communication
* Message prioritization
* High reliability
* Error detection
* Real-time performance
* Reduced wiring complexity

---

# ⚙️ System Working

## Sensor ECU

The sensor ECU performs:

* Speed sensing using ADC
* Gear position detection using switches
* CAN message transmission

Example:

```c id="vgkndu"
can_transmit(SPEED_MSG_ID ,str,2);
```

---

## Dashboard ECU

The dashboard ECU:

* Receives CAN messages
* Identifies message IDs
* Displays corresponding data
* Updates dashboard information in real time

---

# 📦 CAN Message IDs

Defined in `msg_id.h`

| Parameter          | Message ID |
| ------------------ | ---------- |
| Speed              | `0x10`     |
| Gear Position      | `0x20`     |
| RPM                | `0x30`     |
| Engine Temperature | `0x40`     |
| Indicator Status   | `0x50`     |

---

# 🔍 Functional Modules

## 1. ADC Module

Reads analog sensor values such as:

* Vehicle speed
* Engine parameters

Example:

```c id="5mukfy"
unsigned short speed = read_adc(CHANNEL4)/10.33;
```

---

## 2. CAN Module

Responsible for:

* CAN initialization
* Message transmission
* Message reception
* CAN timing configuration

---

## 3. Gear Detection

Gear shifting is simulated using switches:

| Switch  | Function          |
| ------- | ----------------- |
| SWITCH1 | Gear Up           |
| SWITCH2 | Gear Down         |
| SWITCH3 | Collision/Neutral |

---

## 4. LCD Display

Displays:

* Speed
* Gear status
* Other vehicle parameters

---

# 🚀 Project Flow

```text id="zvqf5m"
Sensors → ADC → ECU → CAN Bus → Dashboard ECU → LCD/UART
```

---

# ⚙️ CAN Initialization

The CAN module is configured in:

```text id="7z6npv"
can.c
```

Key configurations include:

* CAN TX/RX pin setup
* CAN timing
* Operation mode
* Receive filters
* Loopback/Normal mode

---

# ▶️ Compilation & Build

Compile using MPLAB X IDE with XC8 compiler.

### Build Steps

1. Open MPLAB X IDE
2. Open project folder
3. Select PIC device
4. Build Project
5. Flash into PIC microcontroller

---

# 📸 Sample Functionality

## Speed Transmission

```c id="j2jkx5"
get_speed();
```

Reads ADC value and sends speed over CAN.

---

## Gear Transmission

```c id="0dhb0j"
get_gear_pos();
```

Detects switch press and transmits gear status.

---

# 🧠 Important Embedded Concepts Used

* Embedded C Programming
* PIC Microcontroller Programming
* CAN Bus Communication
* ADC Interfacing
* UART Communication
* LCD Interfacing
* Switch Debouncing
* Real-Time Data Processing

---

# 🔐 Advantages of CAN

* High-speed communication
* Noise immunity
* Reliable data transfer
* Fault detection capability
* Widely used in automobiles

---

# 📚 Learning Outcomes

This project helps in understanding:

* Automotive communication systems
* Real-time embedded systems
* CAN protocol internals
* ECU communication architecture
* Sensor interfacing
* Embedded firmware development

---

# 🚘 Real-World Applications

* Automotive dashboards
* Vehicle monitoring systems
* Engine control systems
* Industrial CAN networks
* Smart vehicle systems

---

# 👨‍💻 Author

**Blesswin E Vinoy**

Electronics and Communication Engineering

---

# 🎯 Future Improvements

* Add RPM sensor module
* Real-time graphical dashboard
* CAN error frame handling
* OBD-II integration
* TFT display support
* Wireless diagnostics
* IoT-based vehicle monitoring
