#ifndef MQTT_MANAGER_H
#define MQTT_MANAGER_H

#include <ESP8266WiFi.h>
#include <EEPROM.h>
#include <PubSubClient.h>
#include "config.h"

struct MQTTConfig {
  char broker[64];
  uint16_t port;
  char topic[64];
  char username[32];
  char password[32];
};

extern MQTTConfig mqttConfig;
extern WiFiClient espClient;
extern PubSubClient mqttClient;

void saveMQTTConfig();
void loadMQTTConfig();
void resetMQTTConfig();
void sendDataToMQTT(float temp, float hum);
void connectMQTT();

#endif
