#include "wifi_manager.h"

WiFiManager wifiManager;

void setupWiFi() {
  std::vector<const char*> menuItems = { "wifi", "exit" };

  wifiManager.setMenu(menuItems);
  wifiManager.setCaptivePortalEnable(false);
  wifiManager.setShowInfoUpdate(false);
  wifiManager.setShowInfoErase(false);
  wifiManager.setWiFiAutoReconnect(true);

  wifiManager.setCustomHeadElement("<style>\
      body {\
        background-color: #f7f7f7;\
        color: #333;\
        font-family: 'Arial', sans-serif;\
      }\
      input[type='text'],\
      input[type='password'] {\
        width: 100%;\
        padding: 12px;\
        margin-top: 5px;\
        border: 2px solid #ddd;\
        border-radius: 4px;\
        font-size: 14px;\
        font-family: 'Arial', sans-serif;\
        transition: border-color 0.3s ease, box-shadow 0.3s ease;\
      }\
      input[type='text']:focus,\
      input[type='password']:focus {\
        border-color: #333;\
        box-shadow: 0 0 5px rgba(0, 0, 0, 0.1);\
        outline: none;\
      }\
      button,\
      input[type='submit'] {\
        background-color: #333;\
        color: white;\
        border: none;\
        padding: 10px 18px;\
        font-size: 16px;\
        font-family: 'Arial', sans-serif;\
        border-radius: 4px;\
        cursor: pointer;\
        transition: all 0.3s ease;\
      }\
      button:hover,\
      input[type='submit']:hover {\
        background-color: #555;\
      }\
      button:focus,\
      input[type='submit']:focus {\
        outline: none;\
        box-shadow: 0 0 5px rgba(0, 0, 0, 0.2);\
      }\
      button:active,\
      input[type='submit']:active {\
        background-color: #444;\
        transform: translateY(2px);\
      }\
    </style>");

  if (!wifiManager.autoConnect(projectName, defaultPassword)) {
    ESP.restart();
  }

  Serial.println("Connected to WiFi!");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
}
