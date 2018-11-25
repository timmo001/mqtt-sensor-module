#include <main.h>

using namespace std;

DHT dht(DHT_PIN, DHT_TYPE);

void updateState()
{
  float temperature = dht.readTemperature();
  Serial.print("Temperature: ");
  Serial.println(temperature);
  if (!temperature || temperature != temperature)
    return;
  float humidity = dht.readHumidity();
  Serial.print("Humidity: ");
  Serial.println(humidity);
  if (!humidity || humidity != humidity)
    return;
  float heatIndex = dht.computeHeatIndex(temperature, humidity);
  Serial.print("Feels like: ");
  Serial.println(heatIndex);
  if (!heatIndex || heatIndex != heatIndex)
    return;
  float ldr = analogRead(LDR_PIN);
  Serial.print("LDR: ");
  Serial.println(ldr);
  if (!ldr || ldr != heatIndex)
    return;

  const size_t bufferSize = JSON_OBJECT_SIZE(4);
  DynamicJsonBuffer jsonBuffer(bufferSize);

  JsonObject &root = jsonBuffer.createObject();
  root["temperature"] = temperature;
  root["humidity"] = humidity;
  root["heatIndex"] = heatIndex;
  // root["ldr"] = ldr;

  char payload[root.measureLength() + 1];
  root.printTo(payload, sizeof(payload));

  publishState(0, true, payload);
}

void setup()
{
  Serial.begin(115200);

  Serial.println();
  Serial.println();
  Serial.println("--------------------------");
  Serial.println("ESP8266 DHT LDR Module");
  Serial.println("--------------------------");

  setupNetworking(WIFI_SSID, WIFI_PASSWORD, HOSTNAME);
  setupMqtt(MQTT_HOST, MQTT_PORT, MQTT_USERNAME, MQTT_PASSWORD,
            MQTT_TOPIC, MQTT_LWT_TOPIC, HOSTNAME);
  setupOTA(HOSTNAME, OTA_PORT, OTA_PASSWORD);

  // Declare inputs
  pinMode(DHT_PIN, INPUT);
  pinMode(LDR_PIN, INPUT);
}

void loop()
{
  updateState();
  delay(10000);
}
