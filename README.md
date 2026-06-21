# Arduino-MPU6050-Projects

Arduino Uno projects using the MPU6050 Accelerometer and Gyroscope Sensor along with OLED Displays, Push Buttons, and Buzzers for motion sensing, orientation detection, activity monitoring, and real-time visualization applications.

## 1. Objective

The objective of this repository is to develop practical Arduino-based motion sensing and monitoring applications using the MPU6050 sensor and OLED display. These projects demonstrate tilt measurement, motion direction detection, fall detection, step counting, and real-time sensor dashboards using embedded systems and motion tracking technologies.

---

## 2. Components Used

### Hardware Components

* Arduino Uno
* MPU6050 Accelerometer and Gyroscope Sensor
* OLED Display (SSD1306 I2C)
* Push Button
* Active Buzzer Module
* Breadboard
* Jumper Wires

### Software Components

* Arduino IDE
* Adafruit SSD1306 Library
* Adafruit GFX Library
* Wire Library

---

## 3. Circuit Diagram

The projects use different combinations of the following modules.

### OLED Display

| OLED Pin | Arduino Uno |
| -------- | ----------- |
| VCC      | 5V          |
| GND      | GND         |
| SDA      | A4          |
| SCL      | A5          |

### MPU6050 Sensor

| MPU6050 Pin | Arduino Uno |
| ----------- | ----------- |
| VCC         | 5V          |
| GND         | GND         |
| SDA         | A4          |
| SCL         | A5          |

### Push Button

| Button Pin | Arduino Uno |
| ---------- | ----------- |
| One Pin    | D2          |
| Other Pin  | GND         |

### Buzzer Module

| Buzzer Pin | Arduino Uno |
| ---------- | ----------- |
| S          | D8          |
| VCC        | 5V          |
| GND        | GND         |

---

## 4. Code Explanation

This repository contains the following Arduino projects:

### MPU6050 Bubble Level

Uses tilt angle measurements from the MPU6050 to create a digital spirit level. The OLED displays pitch and roll information along with a moving bubble animation similar to a physical spirit level.

### MPU6050 Motion Direction Detector

Detects movement direction using accelerometer data and displays Forward, Backward, Left, or Right directions along with directional arrows on the OLED display.

### MPU6050 Fall Detection System

Monitors acceleration values continuously to detect sudden changes that indicate a fall. A buzzer alarm is activated and the OLED displays a fall warning message while maintaining a fall counter.

### MPU6050 Step Counter

Uses MPU6050 motion data to detect walking activity and count steps in real time. The OLED displays the current step count and motion status.

### MPU6050 Sensor Dashboard

A professional multi-page dashboard that displays acceleration values, tilt angles, activity status, step count, and fall count. A push button is used to switch between dashboard pages.

---

## 5. Output Images

### MPU6050 Bubble Level

<img width="1600" height="1200" alt="WhatsApp Image 2026-06-21 at 7 08 47 AM" src="https://github.com/user-attachments/assets/f9a0f058-78d5-49cc-8178-60583a458af3" />
<img width="1600" height="1200" alt="WhatsApp Image 2026-06-21 at 7 08 47 AM (1)" src="https://github.com/user-attachments/assets/c4acdf1a-1149-48e6-98c7-620a8c0744bd" />


### MPU6050 Motion Direction Detector

<img width="1600" height="1200" alt="WhatsApp Image 2026-06-21 at 7 08 48 AM" src="https://github.com/user-attachments/assets/c60dd1fe-f121-4b09-aa7e-fa4ff05e7320" />
<img width="1600" height="1200" alt="WhatsApp Image 2026-06-21 at 7 08 47 AM" src="https://github.com/user-attachments/assets/144262e5-8dcb-4455-8ce6-d9cbac41a93f" />


### MPU6050 Fall Detection System

<img width="1600" height="1200" alt="WhatsApp Image 2026-06-21 at 7 08 48 AM" src="https://github.com/user-attachments/assets/0a370186-1c88-4bb1-a4b7-b57a0f87ec2f" />


### MPU6050 Step Counter

<img width="1600" height="1200" alt="WhatsApp Image 2026-06-21 at 7 08 48 AM (2)" src="https://github.com/user-attachments/assets/459a3f7a-8a8b-49eb-b565-ca1e4b19def0" />
<img width="1600" height="1200" alt="WhatsApp Image 2026-06-21 at 7 08 48 AM (1)" src="https://github.com/user-attachments/assets/19d111f4-c171-4980-a37e-0df55a1996e0" />


### MPU6050 Sensor Dashboard

<img width="1600" height="1200" alt="WhatsApp Image 2026-06-21 at 7 08 50 AM (2)" src="https://github.com/user-attachments/assets/9eef3948-4e32-4af5-a97c-cd3dbda397f5" />
<img width="1600" height="1200" alt="WhatsApp Image 2026-06-21 at 7 08 50 AM (1)" src="https://github.com/user-attachments/assets/25894f52-2e2d-486e-94e8-062c31a63b1a" />
<img width="1600" height="1200" alt="WhatsApp Image 2026-06-21 at 7 08 50 AM" src="https://github.com/user-attachments/assets/e5b7982b-c00b-4ced-8185-31d4f2a4ad11" />
<img width="1600" height="1200" alt="WhatsApp Image 2026-06-21 at 7 08 49 AM" src="https://github.com/user-attachments/assets/74970ece-3035-44dc-bfea-3332f19387fa" />

---

## 6. Learning Outcome

After completing these projects, learners will be able to:

* Interface the MPU6050 sensor with Arduino Uno using I2C communication.
* Read accelerometer and gyroscope data from the MPU6050.
* Calculate pitch and roll angles for orientation detection.
* Develop digital spirit level applications.
* Detect movement direction using sensor data.
* Implement step counting algorithms using motion sensing.
* Design fall detection and alert systems.
* Create real-time OLED dashboards for sensor visualization.
* Develop motion monitoring and activity tracking applications.
* Apply embedded systems concepts to practical motion sensing projects.

Hemanth A S
