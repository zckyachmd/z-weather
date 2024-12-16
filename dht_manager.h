#ifndef DHT_MANAGER_H
#define DHT_MANAGER_H

#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>

void setupDHT(uint8_t pin, uint8_t type);
void updateDHTData();
float readDHTTemperature(bool inCelsius = true);
float readDHTHumidity();

#endif
