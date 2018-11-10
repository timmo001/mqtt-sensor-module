#include <main.h>

using namespace std;

DHT dht(DHT_PIN, DHT_TYPE);

Ticker updateStateTimer;

void updateState()
{
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();
  float heatIndex = dht.computeHeatIndex(temperature, humidity);

  const size_t bufferSize = JSON_OBJECT_SIZE(3);
  DynamicJsonBuffer jsonBuffer(bufferSize);

  JsonObject &root = jsonBuffer.createObject();
  root["temperature"] = temperature;
  root["humidity"] = humidity;
  root["heatIndex"] = heatIndex;

  char payload[root.measureLength() + 1];
  root.printTo(payload, sizeof(payload));

  publishState(0, true, payload);
}

void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println();

  // Allows terminal to start up
  delay(1000);

  setupNetworking(WIFI_SSID, WIFI_PASSWORD, HOSTNAME);
  setupMqtt(MQTT_HOST, MQTT_PORT, MQTT_USERNAME, MQTT_PASSWORD,
            MQTT_TOPIC, MQTT_LWT_TOPIC, HOSTNAME);
  setupOTA(HOSTNAME, OTA_PORT, OTA_PASSWORD);

  // Declare inputs
  pinMode(DHT_PIN, INPUT);

  updateState();
  updateStateTimer.attach(10, updateState);
}

void loop() {}
