#include <ESP8266WiFi.h>
#include <WiFiManager.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <EEPROM.h>
#include "config.h"
#include "web_pages.h"
#include "web_server.h"
#include "wifi_manager.h"
#include "mqtt_manager.h"
#include "dht_manager.h"

const char* projectName = "Z-Weather";
const char* defaultPassword = "zweather";

unsigned long lastPublishTime = 0;
bool isMqttConfigLoaded = false;

void setup() {
  Serial.begin(115200);
  Serial.println();

  setupDHT(DHTPIN, DHTTYPE);
  setupWiFi();
  setupWebServer();
  MDNS.begin(projectName);

  loadMQTTConfig();

  isMqttConfigLoaded = (mqttConfig.broker[0] != '\0') && (mqttConfig.port != 0) && (mqttConfig.topic[0] != '\0');

  if (isMqttConfigLoaded) {
    mqttClient.setServer(mqttConfig.broker, mqttConfig.port);
    if (!mqttClient.connected()) {
      connectMQTT();
    }
  }

  configTime(GMT_OFFSET_SEC, DAYLIGHT_OFFSET_SEC, NTP_SERVER);
}

void loop() {
  MDNS.update();
  server.handleClient();

  if (!isMqttConfigLoaded) {
    Serial.println("MQTT configuration not loaded. Please set up the MQTT Broker IP, Port, and Topic via the web interface (/config).");
    return;
  }

  mqttClient.loop();

  unsigned long currentMillis = millis();
  if (currentMillis - lastPublishTime >= 60000) {
    lastPublishTime = currentMillis;

    if (mqttClient.connected()) {
      float temp = readDHTTemperature();
      float hum = readDHTHumidity();

      if (temp != -999.0 && hum != -999.0) {
        sendDataToMQTT(temp, hum);
      } else {
        Serial.println("Invalid sensor readings, skipping MQTT publish.");
      }
    } else {
      Serial.printf("MQTT client not connected. Broker: %s, Port: %d. Skipping publish.\n", mqttConfig.broker, mqttConfig.port);
    }
  }
}
