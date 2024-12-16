#include "dht_manager.h"
#include <DHT.h>
#include <Arduino.h>

DHT dht(0, 0);

float cachedTemperature = -999.0;
float cachedHumidity = -999.0;
unsigned long lastDHTUpdateTime = 0;
const unsigned long DHT_UPDATE_INTERVAL = 30000;

void setupDHT(uint8_t pin, uint8_t type) {
  dht = DHT(pin, type);
  dht.begin();
}

void updateDHTData() {
  unsigned long currentMillis = millis();

  if (lastDHTUpdateTime == 0 || (currentMillis - lastDHTUpdateTime >= DHT_UPDATE_INTERVAL)) {
    float temp = dht.readTemperature();
    float hum = dht.readHumidity();

    // Testing only
    // float hum = random(400, 800) / 10.0;
    // float temp = random(150, 300) / 10.0;
    // End: Testing Only

    if (!isnan(temp) && !isnan(hum)) {
      cachedTemperature = temp;
      cachedHumidity = hum;
      lastDHTUpdateTime = currentMillis;
    } else {
      Serial.println("Failed to read DHT sensor data!");
    }
  }
}

float readDHTTemperature(bool inCelsius) {
  updateDHTData();

  if (cachedTemperature == -999.0) {
    return -999.0;
  }

  return dht.computeHeatIndex(cachedTemperature, cachedHumidity, !inCelsius);
}

float readDHTHumidity() {
  updateDHTData();

  return (cachedHumidity == -999.0) ? -999.0 : cachedHumidity;
}
