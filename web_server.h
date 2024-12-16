#ifndef WEB_SERVER_H
#define WEB_SERVER_H

#include <ESP8266WebServer.h>
#include <WiFiUdp.h>
#include <NTPClient.h>
#include "config.h"

extern WiFiUDP ntpUDP;
extern NTPClient timeClient;

extern ESP8266WebServer server;

extern String getFormattedTime(bool formatted = true);
extern void updateTime();

void setupWebServer();

#endif
