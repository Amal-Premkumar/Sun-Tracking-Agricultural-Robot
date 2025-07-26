# Sun-Tracking-Agricultural-Robot

# 🌞 Sun Tracking Agricultural Robot

An **autonomous smart farming robot** designed to **seed**, **water**, and **monitor temperature**, while **tracking sunlight** through a solar panel that rotates based on light direction. The robot includes **wireless control** and real-time monitoring via a custom web interface.

## 🚜 Project Overview

This robot is built for **precision farming** and operates **autonomously** after the user sets the **length and breadth** of the field. Key operations include:

- **Seeding**
- **Watering**
- **Temperature sensing**
- **Solar panel light tracking** for energy optimization

All functionalities are remotely managed via a **private web interface** hosted through an **ESP8266 Wi-Fi module**.

## 🌟 Features

- ✅ **Autonomous movement** across the field in a zig-zag path  
- 🌱 **Seeding mechanism** with toggle control  
- 💧 **Controlled watering system**  
- 🌡️ **Atmospheric temperature monitoring**  
- ☀️ **Sunlight tracking solar panel** using dual **LDR sensors**  
- 🔁 **Automatic solar panel rotation** toward the brighter light source  
- 📶 **Wireless control with ESP8266**  
- 🌐 **Custom web dashboard** to:
  - Toggle **watering** and **seeding**
  - View **real-time temperature**

## 🧠 Technologies Used

- **Arduino Nano** – Main controller for motor & logic control  
- **ESP8266 Wi-Fi Module** – Hosts web interface and receives commands  
- **LDR Sensors (x2)** – Detect sunlight direction  
- **Servo Motor** – Rotates the solar panel  
- **DHT11** – Temperature sensing  
- **DC Motor** – Movement and mechanism handling  

## 🔧 How It Works

1. User inputs **field dimensions** via the web dashboard
2. Robot navigates field autonomously
3. Solar panel uses **dual LDRs** to detect light and **rotates** to face the sun
4. **Watering and seeding** actions are toggled remotely
5. **Temperature data** is captured and shown on the website

## ☀️ Solar Panel Tracking System

- Mounted on a **servo motor**
- Controlled by comparing **light intensity** from **two LDRs**
- Continuously aligns itself toward the **stronger light source** for maximum solar efficiency

## 📷 Project Demo
![1748444256582](https://github.com/user-attachments/assets/4a03c50b-c0af-4790-ab5f-75dee1e581f2)

