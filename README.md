# MQTT Sensor Module

An MQTT sensor module. Supports DHT sensors and LDR sensors so far

## Hardware Setup

TBD

## Software Setup

- Using Atom or VS Code, install [Platform IO](https://platformio.org/platformio-ide)
- Once setup, install the `esp8266` embedded platform
- Copy `src/setup-template.h` to `src/setup.h` and add your network, MQTT and lighting setup information. Take note of the `deviceName` you set. You will need this later to send MQTT messages.
- Build the project (Ctrl+Alt+B) and check for any errors
- Upload to your board of choice (Ctrl+Alt+U). This project was created for the `Wemos D1 mini` but can be configured to work with another WiFi board with some tinkering.

## Example Home Assistant Configuration

TBD
