# MQTT Sensor Module

An MQTT sensor module. Supports DHT sensors and LDR sensors so far

## Hardware Setup

- Add a DHT device to one of your digital pins of your chip. Take note of
 the pin for later.
- Add an analog LDR to your analog pin (A0) and take not of it for later.

## Software Setup

- Using Atom or VS Code, install [Platform IO](https://platformio.org/platformio-ide)
- Once setup, install the `esp8266` embedded platform
- Copy `src/setup-template.h` to `src/setup.h` and add your network, MQTT and
 other setup information. Take note of the `HOSTNAME` you set. You will need
 this later to send MQTT messages.
- Build the project (Ctrl+Alt+B) and check for any errors
- Upload to your board of choice (Ctrl+Alt+U). This project was created for
 the `NodeMCU ESP8266` board but can be configured to work with another WiFi
 board with some tinkering.

## Example Home Assistant Configuration

```yaml
sensor:
  - platform: mqtt_json
    name: 'Temperature'
    state_topic: 'sensor/1'
    availability_topic: 'sensor/1/LWT'
  - platform: mqtt_json
    name: 'Feels like'
    state_topic: 'sensor/1'
    availability_topic: 'sensor/1/LWT'
  - platform: mqtt_json
    name: 'Humidity'
    state_topic: 'sensor/1'
    availability_topic: 'sensor/1/LWT'
```
