/*
 * @file main.cpp
 * @author jonnie Walker
 * @brief ESP32_LU9685-20U-Test
 * @version 0.1
 * @date 2023-11-29
 * 
 * @copyright Copyright (c) 2023
 *
 * ---------------------------------------------------------------
 * Modified by @RodPy
 * Added detailed comments in English for clarity and documentation.
 *
 * LU9685-20U-Test
 * Defines the macro DEVICE_ADDRESS to simplify modification of the device address.
 * A new function sendCommand was created to send instructions and avoid code duplication.
 * Simplifies command calls by grouping Wire.beginTransmission, Wire.write, and Wire.endTransmission.
 * Defines four main functions to interact with the LU9685 servo controller.
 * ---------------------------------------------------------------
*/

#include <Wire.h>   // Include the I2C communication library

#define DEVICE_ADDRESS 0x80  // I2C device address of the LU9685-20CU controller

void setup() {

  Wire.begin();             // Initialize the I2C bus as master
  Serial.begin(115200);     // Start serial communication for debugging output
  
}

void loop() {

  resetDevice();            // Send reset command to initialize the LU9685 controller
  
  controlChannel(1, 45);    // Move servo on channel 1 to 90 degrees
  delay(1000);              // Wait 1 second
  
  controlChannel(0, 180);   // Move servo on channel 0 to 180 degrees
  delay(1000);              // Wait 1 second
  
  controlAllChannels(30);   // Move all servos simultaneously to 30 degrees
  delay(1000);              // Wait 1 second
  
}

/*
 * sendCommand()
 * Sends a command array to the LU9685 controller via I2C
 * This function centralizes the transmission process to avoid repeating code
 */
void sendCommand(byte command[], byte length) {

  Wire.beginTransmission(DEVICE_ADDRESS);  // Start communication with the LU9685 device
  Wire.write(command, length);             // Send the command bytes to the device
  Wire.endTransmission();                  // End the I2C transmission
  delay(10);                               // Small delay to allow the device to process the command
  
}

/*
 * resetDevice()
 * Sends a reset command to the LU9685 controller
 * This resets internal states of the servo driver
 */
void resetDevice() {

  byte command[] = {0xFB, 0xFB};  // Reset command sequence defined by the LU9685 protocol
  sendCommand(command, sizeof(command));  // Send reset command
  
}

/*
 * controlChannel()
 * Controls a specific servo channel
 * channel: servo index (0–15)
 * angle: servo angle in degrees (0–180)
 */
void controlChannel(byte channel, byte angle) {

  byte command[] = {channel, angle};   // Command format: [channel, angle]
  sendCommand(command, sizeof(command));  // Send command to LU9685
  
}

/*
 * controlAllChannels()
 * Moves all servo channels to the same angle simultaneously
 * angle: target servo angle (0–180 degrees)
 */
void controlAllChannels(byte angle) {

  byte command[] = {0xFD, angle};   // Special command for controlling all channels
  sendCommand(command, sizeof(command));  // Send broadcast command
  
}