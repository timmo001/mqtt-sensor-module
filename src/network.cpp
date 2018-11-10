#include <network.h>

using namespace std;

const char *ssid;
const char *pass;

WiFiEventHandler wifiConnectHandler;
WiFiEventHandler wifiDisconnectHandler;

Ticker wifiReconnectTimer;
Ticker mqttReconnectTimer;

void connectToWifi()
{
  Serial.println("Connecting to Wi-Fi...");
  if (WiFi.status() != WL_CONNECTED)
    WiFi.begin(ssid, pass);
}

void onWifiConnect(const WiFiEventStationModeGotIP &event)
{
  Serial.println("Connected to Wi-Fi.");
  connectToMqtt();
}

void onWifiDisconnect(const WiFiEventStationModeDisconnected &event)
{
  Serial.println("Disconnected from Wi-Fi.");
  mqttReconnectTimer.detach(); // ensure we don't reconnect to MQTT while reconnecting to Wi-Fi
  wifiReconnectTimer.once(2, connectToWifi);
}

void onMqttDisconnect(AsyncMqttClientDisconnectReason reason)
{
  Serial.println("Disconnected from MQTT.");

  if (WiFi.isConnected())
    mqttReconnectTimer.once(2, connectToMqtt);
}

void setupNetworking(const char *WIFI_SSID, const char *WIFI_PASSWORD,
                     const char *HOSTNAME)
{
  ssid = WIFI_SSID;
  pass = WIFI_PASSWORD;

  wifiConnectHandler = WiFi.onStationModeGotIP(onWifiConnect);
  wifiDisconnectHandler = WiFi.onStationModeDisconnected(onWifiDisconnect);

  WiFi.hostname(HOSTNAME);
  connectToWifi();
}
