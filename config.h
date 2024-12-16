#ifndef CONFIG_H
#define CONFIG_H

#include <ESP8266WiFi.h>

#define DHTPIN 4
#define DHTTYPE DHT22

#define NTP_SERVER "pool.ntp.org"
#define GMT_OFFSET_SEC 25200
#define DAYLIGHT_OFFSET_SEC 0
#define NTP_UPDATE_INTERVAL 600000

#define MQTT_BROKER_ADDR 0

extern const char *projectName;
extern const char *defaultPassword;

#endif
