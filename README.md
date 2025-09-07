# Arduino based Automatic Ipomoea Aquatica Monitoring and Watering Tool
An Arduino-based project designed to create a smart, automated environment for plants. AgriShield monitors key environmental factors—temperature, soil moisture, light, and plant height—and provides real-time feedback and automated responses to ensure optimal growing conditions.

## 📜 About the Project

This project was created to help automate plant care by building an intelligent monitoring system. It uses a variety of sensors to collect data about the plant's surroundings and its growth. The system displays this information on an LCD screen and through the serial monitor. It also triggers alerts with LEDs and a buzzer for critical conditions (e.g., high temperature) and can control a water pump via a relay for automated irrigation.

This is an excellent project for anyone interested in electronics, programming, and agriculture technology.

## ✨ Key Features

* **🌡️ Real-time Temperature Monitoring:** Uses a DHT11 sensor to monitor the ambient temperature.
* **💧 Automatic Watering System:** A soil moisture sensor detects dry soil and activates a relay to control a water pump.
* **📏 Plant Growth Tracking:** An ultrasonic sensor measures the plant's height, providing data on its growth over time.
* **☀️ Light Level Detection:** An LDR sensor determines whether it's day or night, with data displayed on a secondary screen.
* **🖥️ Dual-Screen LCD Display:** Shows primary sensor data (temperature, height) and periodically switches to a secondary screen with condition information (time of day, soil status).
* **🚨 Audible & Visual Alerts:** A buzzer and a set of RGB LEDs provide immediate alerts for conditions that require attention, such as excessively high temperatures or plant overgrowth.
* **🚀 Animated Startup Sequence:** A fun, animated startup screen on the LCD with sound effects.

## 🛠️ Hardware Required

* Arduino Uno (or any compatible board)
* DHT11 Temperature and Humidity Sensor
* HC-SR04 Ultrasonic Distance Sensor
* Soil Moisture Sensor Module
* LDR (Light Dependent Resistor)
* 16x2 I2C LCD Display
* 5V Single Channel Relay Module
* Active Buzzer
* LEDs (1x Red, 1x Yellow, 1x Green)
* Resistors (3x 220Ω for LEDs, 1x 10kΩ for LDR)
* Jumper Wires
* Breadboard

## ⚙️ Software & Libraries

1.  **[Arduino IDE](https://www.arduino.cc/en/software)**
2.  **Required Libraries:**
    * `LiquidCrystal_I2C`: For controlling the I2C LCD. You can install this from the Arduino Library Manager.
    * `DHT sensor library` by Adafruit: For reading data from the DHT11 sensor.

## 🔌 Wiring & Schematic

Connect the components to the Arduino as defined in the code:

| Component Pin | Arduino Pin |
| :--- | :--- |
| **Ultrasonic Sensor**| |
| `TRIG_PIN` | Digital Pin 6 |
| `ECHO_PIN` | Digital Pin 5 |
| **DHT11 Sensor** | |
| `DHT_PIN` | Digital Pin 3 |
| **LDR Sensor** | |
| `LDR_PIN` | Digital Pin 2 |
| **Soil Moisture** | |
| `SOIL_PIN` | Analog Pin A2 |
| **Actuators** | |
| `BUZZER_PIN` | Digital Pin 7 |
| `GREEN_PIN` (LED) | Digital Pin 9 |
| `YELLOW_PIN` (LED) | Digital Pin 10 |
| `RED_PIN` (LED) | Digital Pin 11 |
| `RELAY_PIN` | Digital Pin 12 |
| **I2C LCD Display** | |
| `SDA` | Analog Pin A4 |
| `SCL` | Analog Pin A5 |

## 👨‍💻 How It Works

### Setup
1.  **Initialization:** In the `setup()` function, the script initializes the Serial Monitor, LCD, DHT sensor, and sets the pin modes for all sensors and actuators.
2.  **Startup Animation:** The `animasiteks()` function runs once, creating a cool text animation and sound sequence on the LCD to indicate the system is starting.

### Main Loop
The `loop()` function continuously performs the following actions:

1.  **Read Sensors:** It reads the current temperature, calculates plant height (`Tita`), measures the light level (`Waktu`), and checks the soil moisture (`value`).
2.  **Display Data:**
    * It prints all sensor readings to the **Serial Monitor** for debugging and logging.
    * It displays the temperature and plant height on the **primary LCD screen**.
3.  **Check Conditions & Alert:**
    * **Temperature Alert:**
        * If the temperature is between 30-35°C, the **yellow LED** blinks.
        * If the temperature exceeds 35°C, the **red LED** blinks and the **buzzer** sounds, signaling a critical condition.
        * Otherwise, the **green LED** stays on, indicating normal conditions.
    * **Plant Height Alert:** If the plant height exceeds 48 cm, the buzzer and red LED briefly activate.
4.  **Automated Watering:** The script reads the soil moisture value. If the value is above `500` (indicating dry soil), it activates the `RELAY_PIN`, which can be connected to a water pump to irrigate the plant.
5.  **Secondary Display:** Every 60 seconds (`kondisiInterval`), the `paneldua()` function is called. It temporarily clears the main display to show the time of day (based on LDR readings) and the soil condition ("Basah" or "Kering").

## 🚀 Installation & Usage

1.  **Assemble the Circuit:** Connect all the hardware components according to the wiring table above.
2.  **Install Libraries:** Open the Arduino IDE, go to `Sketch` -> `Include Library` -> `Manage Libraries...` and install the `LiquidCrystal_I2C` and `DHT sensor library`.
3.  **Open the Code:** Open the `.ino` file in the Arduino IDE.
4.  **Connect & Upload:** Connect your Arduino board to your computer and upload the sketch.
5.  **Monitor:** Open the Serial Monitor at a baud rate of `9600` to see detailed sensor data. The LCD will display the primary interface.

### Calibration
You may need to adjust the following `#define` values at the top of the code to calibrate the sensors for your specific environment:
* `wet`: The analog reading from the soil sensor when it is fully saturated.
* `dry`: The analog reading when the soil is completely dry.
* `LDR_THRESHOLD`: The LDR reading that differentiates between day (`< 555`) and night (`>= 555`).
* `tinggi_ruangan`: In the `HitungTita()` function, change `38.5` to the actual distance (in cm) from the ultrasonic sensor to the base of the plant pot.
