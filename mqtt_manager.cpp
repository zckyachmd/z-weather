#include "mqtt_manager.h"
#include "web_server.h"

MQTTConfig mqttConfig;
WiFiClient espClient;
PubSubClient mqttClient(espClient);

void saveMQTTConfig() {
  EEPROM.begin(512);
  EEPROM.put(MQTT_BROKER_ADDR, mqttConfig);
  EEPROM.commit();
  EEPROM.end();
}

void loadMQTTConfig() {
  EEPROM.begin(512);
  EEPROM.get(MQTT_BROKER_ADDR, mqttConfig);
  if (mqttConfig.port == 0) {
    mqttConfig.port = 1883;
    strncpy(mqttConfig.topic, "weather/", sizeof(mqttConfig.topic));
  }
  EEPROM.end();
}

void resetMQTTConfig() {
  EEPROM.begin(512);
  memset(&mqttConfig, 0, sizeof(MQTTConfig));
  mqttConfig.port = 1883;
  strncpy(mqttConfig.topic, "weather/", sizeof(mqttConfig.topic));
  EEPROM.put(MQTT_BROKER_ADDR, mqttConfig);
  EEPROM.commit();
  EEPROM.end();
}

void sendDataToMQTT(float temp, float hum) {
  String timeStamp = getFormattedTime(false);
  String payload = "{\"temperature\": " + String(temp) + ", \"humidity\": " + String(hum) + ", \"timestamp\": \"" + timeStamp + "\"}";

  mqttClient.publish(String(mqttConfig.topic).c_str(), payload.c_str());

  Serial.println("Data sent to MQTT: " + payload);
}

void connectMQTT() {
  unsigned long startMillis = millis();
  unsigned long timeout = 10000;
  unsigned long retryInterval = 5000;

  while (!mqttClient.connected() && (millis() - startMillis < timeout)) {
    Serial.print("Trying MQTT connection...");

    if (mqttClient.connect(projectName)) {
      Serial.println("Connected to MQTT broker");
      return;
    } else {
      Serial.print("Failed, rc=");
      Serial.print(mqttClient.state());
      Serial.println(" Will try again next loop.");

      unsigned long currentMillis = millis();
      while (millis() - currentMillis < retryInterval) {
        yield();
      }
    }
  }

  if (!mqttClient.connected()) {
    Serial.println("Timeout reached, unable to connect to MQTT broker.");
  }
}
