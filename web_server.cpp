#include "WString.h"
#include "wifi_manager.h"
#include "web_server.h"
#include "web_pages.h"
#include "mqtt_manager.h"
#include "DHT_manager.h"

ESP8266WebServer server(80);
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, NTP_SERVER, GMT_OFFSET_SEC, NTP_UPDATE_INTERVAL);

String getFormattedTime(bool formatted) {
  timeClient.update();

  if (formatted) {
    String timeWithZone = timeClient.getFormattedTime().substring(0, 5);
    return timeWithZone;
  } else {
    return timeClient.getFormattedTime();
  }
}

String applyHtmlTemplate(const String& title, const String& header, const String& content) {
  String page = String((const __FlashStringHelper*)html_template);

  String placeholders[] = { "%TITLE%", "%HEADER%", "%CONTENT%" };
  String values[] = { title + (" / ") + projectName, header, content };

  for (int i = 0; i < 3; i++) {
    String placeholder = placeholders[i];
    String value = values[i];

    while (page.indexOf(placeholder) != -1) {
      page.replace(placeholder, value);
    }
  }

  page.replace("%HEADER%", header);

  return page;
}

void setupWebServer() {
  server.on("/", HTTP_GET, []() {
    String content = applyHtmlTemplate("Home", projectName, String((const __FlashStringHelper*)index_html));
    server.send(200, "text/html", content);
  });

  server.on("/monitoring", HTTP_GET, []() {
    server.send(200, "text/html", applyHtmlTemplate("Monitoring", projectName, String((const __FlashStringHelper*)monitoring_html)));
  });

  server.on("/sensor-data", HTTP_GET, []() {
    float temperature = readDHTTemperature();
    float humidity = readDHTHumidity();
    String currentTime = getFormattedTime(false);

    String jsonResponse = "{";
    jsonResponse += "\"temperature\":";

    if (temperature != -999.0) {
      jsonResponse += String(temperature);
    } else {
      jsonResponse += "\"Error\"";
    }

    jsonResponse += ",\"humidity\":";

    if (humidity != -999.0) {
      jsonResponse += String(humidity);
    } else {
      jsonResponse += "\"Error\"";
    }

    jsonResponse += ",\"timeServer\":\"" + currentTime + "\"";
    jsonResponse += "}";

    server.send(200, "application/json", jsonResponse);
  });

  server.on("/device-info", HTTP_GET, []() {
    String currentTime = getFormattedTime(true);

    String jsonResponse = "{";
    jsonResponse += "\"timeServer\":\"" + currentTime + "\",";
    jsonResponse += "\"freeMemory\":" + String(ESP.getFreeHeap() / 1024) + ",";
    jsonResponse += "\"wifiSSID\":\"" + WiFi.SSID() + "\",";
    jsonResponse += "\"wifiSignalStrength\":" + String(WiFi.RSSI()) + ",";
    jsonResponse += "\"deviceIP\":\"" + WiFi.localIP().toString() + "\"";
    jsonResponse += "}";

    server.send(200, "application/json", jsonResponse);
  });

  server.on("/config", HTTP_GET, []() {
    String content = String((const __FlashStringHelper*)config_html);
    content.replace("%MQTT_BROKER%", String(mqttConfig.broker));
    content.replace("%MQTT_PORT%", String(mqttConfig.port));
    content.replace("%MQTT_TOPIC%", String(mqttConfig.topic));
    content.replace("%MQTT_USERNAME%", String(mqttConfig.username));
    content.replace("%MQTT_PASSWORD%", String(mqttConfig.password));

    server.send(200, "text/html", applyHtmlTemplate("MQTT Configuration", projectName, content));
  });

  server.on("/config", HTTP_POST, []() {
    String broker = server.arg("mqtt_broker");
    uint16_t port = server.arg("mqtt_port").toInt();
    String topic = server.arg("mqtt_topic");
    String username = server.arg("mqtt_username");
    String password = server.arg("mqtt_password");

    if (broker.length() > 0 && topic.length() > 0) {
      strncpy(mqttConfig.broker, broker.c_str(), sizeof(mqttConfig.broker));
      mqttConfig.port = port;
      strncpy(mqttConfig.topic, topic.c_str(), sizeof(mqttConfig.topic));
      strncpy(mqttConfig.username, username.c_str(), sizeof(mqttConfig.username));
      strncpy(mqttConfig.password, password.c_str(), sizeof(mqttConfig.password));

      saveMQTTConfig();

      String content = applyHtmlTemplate("MQTT Configuration", projectName, String((const __FlashStringHelper*)config_post_html));
      server.send(200, "text/html", content);
      delay(1000);
      ESP.restart();
    }
  });

  server.on("/reset", HTTP_GET, []() {
    String content = applyHtmlTemplate("Reset Configuration", projectName, String((const __FlashStringHelper*)reset_html));
    server.send(200, "text/html", content);
  });

  server.on("/reset", HTTP_POST, []() {
    String content = applyHtmlTemplate("Reset Configuration", projectName, String((const __FlashStringHelper*)reset_post_html));
    content.replace("%DEFAULT_PASSWORD%", String(defaultPassword));
    server.send(200, "text/html", content);

    delay(1000);

    wifiManager.resetSettings();
    resetMQTTConfig();
    ESP.restart();
  });

  server.begin();
}
