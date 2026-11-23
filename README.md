🛡️ BattleGuard
Advanced Military Access Control and Authentication System Using RFID and CAN Communication
BattleGuard Project

📌 1. Project Overview
BattleGuard is a multi-node embedded access-control and authentication system designed for secure entry management in restricted areas.

The system integrates RFID authentication, CAN communication, GSM notification, LCD monitoring, LED and buzzer indication, and servo-based automatic gate control using LPC2129 ARM7 microcontrollers.

The project demonstrates the practical implementation of:

Embedded C Programming
ARM7 LPC2129
UART Communication
CAN Communication
RFID Interfacing
GSM Communication
PWM
Servo Motor Control
LCD Interfacing
GPIO
Multi-node Embedded System Design
📝 2. Abstract
Security and controlled access are important requirements in restricted and sensitive environments. Manual verification can be time-consuming and may increase the possibility of unauthorized access.

BattleGuard is an automated RFID-based access-control system developed using multiple LPC2129 microcontroller nodes.

An EM-18 RFID reader detects the RFID tag and sends the identification data to the first controller through UART communication. The controller compares the received RFID ID with a predefined authorized ID.

Based on the authentication result, a CAN message is transmitted to the other controller nodes.

For an authorized RFID tag, the gate-control node operates a servo motor using PWM to open the gate for a predefined period and then automatically closes it.

For an unauthorized RFID tag, the gate remains closed while the 20×4 LCD displays the access status and the LED and buzzer provide an alert indication. A GSM module can also be used to send an SMS notification for unauthorized access.

The project demonstrates a practical distributed multi-node embedded system using CAN communication.

🎯 3. Objectives
Implement RFID-based authentication.
Read RFID data using UART communication.
Compare the scanned RFID with a predefined authorized ID.
Transfer authentication status using CAN communication.
Control a servo motor using PWM.
Implement automatic gate opening and closing.
Display authentication status using a 20×4 LCD.
Provide LED and buzzer alerts for unauthorized access.
Send GSM notifications for unauthorized access.
Demonstrate multi-node communication using LPC2129.
🏗️ 4. System Architecture
                         ┌─────────────────────┐
                         │      RFID TAG       │
                         └──────────┬──────────┘
                                    │
                                    ▼
                         ┌─────────────────────┐
                         │    EM-18 RFID       │
                         │       READER        │
                         └──────────┬──────────┘
                                    │
                                   UART
                                    │
                                    ▼
               ┌────────────────────────────────────┐
               │              ECU 1                 │
               │             LPC2129                │
               │                                    │
               │  RFID Authentication               │
               │  UART Communication                │
               │  GSM Notification                  │
               │  CAN Transmission                  │
               └─────────────────┬──────────────────┘
                                 │
                                 │ CAN BUS
                       ┌─────────┴─────────┐
                       │                   │
                       ▼                   ▼
             ┌───────────────────┐  ┌───────────────────┐
             │      ECU 2        │  │      ECU 3        │
             │     LPC2129       │  │     LPC2129       │
             │                   │  │                   │
             │ CAN Reception     │  │ CAN Reception     │
             │ PWM Control       │  │ 20×4 LCD          │
             │ Servo Control     │  │ LED + Buzzer      │
             └─────────┬─────────┘  └───────────────────┘
                       │
                       ▼
                ┌──────────────┐
                │ Servo Motor  │
                │ Gate Control │
                └──────────────┘
🔧 5. Hardware Components
Microcontroller
LPC2129 ARM7TDMI-S
ARM7 microcontroller
Built-in CAN controller
UART interface
PWM generation
GPIO
RFID Section
EM-18 RFID Reader
RFID Card / RFID Tag
Communication
CAN Bus
UART
GSM Module
Display and Alert
20×4 LCD
LED
Buzzer
Gate Control
Servo Motor
PWM Control
Other Components
Power Supply
Connecting Wires
CAN Transceiver / Interface
Development Board
💻 6. Software and Development Tools
Embedded C
Keil µVision
ARM7 LPC2129 Development Environment
CAN Debugging Tools
⚙️ 7. Working Principle
Step 1 — RFID Scanning
The RFID tag is placed near the EM-18 RFID reader.

The reader detects the RFID tag and obtains its identification value.

The RFID data is transferred to the LPC2129 through UART communication.

RFID Tag
   ↓
EM-18 RFID Reader
   ↓
UART
   ↓
LPC2129
Step 2 — RFID Authentication
The LPC2129 receives the RFID identification value through UART.

The received RFID ID is compared with the predefined authorized RFID ID.

RFID ID
   ↓
LPC2129
   ↓
Compare with Authorized ID
   ↓
┌───────────────┐
│    Match ?    │
└───────┬───────┘
        │
   ┌────┴────┐
   │         │
  YES        NO
   │         │
   ▼         ▼
 VALID     INVALID
Step 3 — CAN Communication
After RFID authentication, ECU1 sends the authentication result to ECU2 and ECU3 through the CAN bus.

RFID Authentication
        ↓
      ECU1
        ↓
   CAN Controller
        ↓
      CAN BUS
        ↓
   ┌────┴────┐
   │         │
   ▼         ▼
  ECU2      ECU3
 Servo      LCD
 Motor      LED
 Gate       Buzzer
Step 4 — Gate Control
ECU2 receives the authentication result through the CAN bus and controls the servo motor.

CAN Message
     ↓
    ECU2
     ↓
 Check ByteA
     ↓
 ┌────┴────┐
 │         │
0x01      0x02
 │         │
 ▼         ▼
VALID    INVALID
 │         │
 ▼         ▼
Servo    Servo
 90°      0°
 │         │
 ▼         ▼
Gate     Gate
Open     Closed
Step 5 — LCD Display
ECU3 receives the authentication result through the CAN bus and displays the access status on the 20×4 LCD.

CAN Message
     ↓
    ECU3
     ↓
 Check ByteA
     ↓
 ┌────┴────┐
 │         │
0x01      0x02
 │         │
 ▼         ▼
VALID    INVALID
 │         │
 ▼         ▼
ACCESS   ACCESS
GRANTED  DENIED
For Valid RFID
VALID RFID
ACCESS GRANTED
For Invalid RFID
INVALID RFID
ACCESS DENIED
LCD Startup Information
The LCD also displays the system information during startup.

BattleGuard: Advance
MILITARY ACCESS
RFID AUTHENTICATION
CAN COMMUNICATION
Step 6 — Alert System
When an invalid RFID tag is detected, ECU3 activates the LED and buzzer to indicate unauthorized access.

INVALID RFID
     ↓
    ECU3
     ↓
LCD → ACCESS DENIED
     ↓
LED + Buzzer
     ↓
Security Alert
The GSM module can also send an SMS notification for unauthorized access.

INVALID RFID
     ↓
GSM Module
     ↓
SMS Notification
Step 7 — Continuous RFID Scanning
After the authentication process is completed, the system returns to the RFID scanning state and waits for the next RFID tag.

RFID Tag
   ↓
EM-18 RFID Reader
   ↓
UART
   ↓
LPC2129
   ↓
Read Next RFID Tag
Step 8 — System Monitoring
The system continuously monitors RFID authentication and access status through the connected ECUs.

RFID Scanning
      ↓
Authentication
      ↓
CAN Communication
      ↓
  ┌─────┴─────┐
  │           │
 ECU2        ECU3
  │           │
  ▼           ▼
 Gate      LCD Display
Control    + LED + Buzzer
Step 9 — Complete System Operation
The complete BattleGuard system operates as a multi-node authentication and access-control system.

             RFID TAG
                 ↓
          ┌──────────┐
          │   ECU1   │
          │ RFID +   │
          │ GSM + CAN│
          └────┬─────┘
               │
               │ CAN
               ▼
          ┌──────────┐
          │   ECU2   │
          │  Servo   │
          │  Gate    │
          └──────────┘

               CAN
                │
                ▼
          ┌──────────┐
          │   ECU3   │
          │ LCD +    │
          │ LED +    │
          │ Buzzer   │
          └──────────┘
Valid RFID Flow
VALID RFID
    ↓
Access Granted
    ↓
Gate Opens
    ↓
LCD Shows VALID RFID
    ↓
After Delay → Gate Closes
Invalid RFID Flow
INVALID RFID
    ↓
Access Denied
    ↓
Gate Remains Closed
    ↓
LCD Shows INVALID RFID
    ↓
LED / Buzzer Alert
✅ 8. Advantages
Provides secure RFID-based authentication.
Prevents unauthorized access.
Provides fast and automatic access verification.
Uses CAN communication for reliable communication between multiple ECUs.
Servo motor provides automatic gate opening and closing.
LCD displays authentication and access status.
LED and buzzer provide visual and audible alerts.
Modular multi-node architecture makes the system easy to expand.
Reduces the need for manual access verification.
Suitable for real-time access-control applications.
🎯 9. Applications
Military base access control
Defence facility security
Restricted-area access control
Secure laboratory access
Government facility security
Industrial security systems
Railway and metro restricted-area access
Warehouse and storage-area security
Parking and vehicle access control
Smart building access control
👤 Author
Manish kumar V B.E. Electrical and Electronics Engineering Graduate Embedded Systems & Embedded C Aspirant

