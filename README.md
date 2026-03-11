# LU9685 Arduino Controller

Arduino examples for controlling the **LU9685-20CU 16-channel servo controller** via I2C.

Modified and documented by **@RodPy**

---

# Overview

This repository provides a minimal Arduino example to control the **LU9685-20CU 16-channel servo controller** using the I2C protocol.

Unlike the PCA9685 controller, the **LU9685 uses a different command protocol**, so common libraries like the Adafruit PCA9685 library will not work directly.

This project demonstrates the basic commands needed to:

- reset the controller
- control a single servo channel
- control all channels simultaneously

The code is intentionally simple so it can easily be integrated into robotics projects.

---

# Hardware

Tested with the following module:

LU9685-20CU 16-Channel Servo Controller

Reference hardware used for this project:

https://www.aliexpress.us/item/3256805152796443.html

⚠️ Note  
This board is **similar to PCA9685 but uses a different communication protocol**.

---

# Features

- Control **up to 16 servos**
- Simple **I2C command protocol**
- Compatible with **Arduino, ESP32, and other I2C microcontrollers**
- Minimal dependencies (only `Wire.h`)
- Lightweight implementation

---

# Wiring

## I2C connection

| LU9685 Pin | Arduino UNO |
|-------------|-------------|
| SDA | A4 |
| SCL | A5 |
| DUCC | 5V |
| GND | GND |

For ESP32:

| LU9685 | ESP32 |
|------|------|
| SDA | GPIO21 |
| SCL | GPIO22 |

---

## Servo Power Supply

Servos must be powered with an **external power supply**.

| LU9685 | Power Supply |
|------|------|
| V+ | 5V |
| GND | GND |

⚠️ Important  
Do **not power servos directly from the Arduino**.

Always connect the **power supply GND and Arduino GND together**.

---

# I2C Address

Default device address:
0x80

Some I2C scanners may display this as:
0x40


because of the 7-bit vs 8-bit addressing difference.

---

# Protocol

The LU9685 uses a very simple I2C command structure.

### Control a single servo

because of the 7-bit vs 8-bit addressing difference.

---

# Protocol

The LU9685 uses a very simple I2C command structure.

### Control a single servo
[channel, angle]

Example:
[1,90]


Moves **servo channel 1** to **90°**.

---

### Control all servos
[0xFD, angle]

Example:
[0xFD, 30]

Moves **all servos** to **30°**.

---

### Reset device
0xFB

Resets the internal controller state.

---

# Example Code

```cpp
#include <Wire.h>

#define DEVICE_ADDRESS 0x80

void setup() {
  Wire.begin();
}

void loop() {

  resetDevice();

  controlChannel(1, 90);
  delay(1000);

  controlChannel(0, 180);
  delay(1000);

  controlAllChannels(30);
  delay(1000);
}

void sendCommand(byte command[], byte length) {
  Wire.beginTransmission(DEVICE_ADDRESS);
  Wire.write(command, length);
  Wire.endTransmission();
  delay(10);
}

void resetDevice() {
  byte command[] = {0xFB, 0xFB};
  sendCommand(command, sizeof(command));
}

void controlChannel(byte channel, byte angle) {
  byte command[] = {channel, angle};
  sendCommand(command, sizeof(command));
}

void controlAllChannels(byte angle) {
  byte command[] = {0xFD, angle};
  sendCommand(command, sizeof(command));
}


