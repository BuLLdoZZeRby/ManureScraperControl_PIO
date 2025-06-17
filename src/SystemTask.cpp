#include "SystemTask.h"
#include <SPIFFS.h>
#include <WiFi.h>
#include <Arduino.h>
#include "WebServerTask.h"

extern const char* SSID;
extern const char* PASSWORD;
extern const char* AP_SSID;
extern const char* AP_PASS;

void SystemTask(void* pv) {
  if (!SPIFFS.begin(true)) {
    Serial.println("[System] SPIFFS mount failed");
  } else {
    Serial.println("[System] SPIFFS mounted");
  }

  WiFi.mode(WIFI_MODE_STA);
  WiFi.begin(SSID, PASSWORD);
  Serial.print("[System] Connecting to Wi-Fi ");
  Serial.print(SSID);
  unsigned long start = millis();
  while (WiFi.status() != WL_CONNECTED && millis() - start < 10000) {
    vTaskDelay(pdMS_TO_TICKS(500));
  }
  if (WiFi.status() == WL_CONNECTED) {
    Serial.println(String("\n[System] Wi-Fi connected, IP: ") + WiFi.localIP().toString());
  } else {
    WiFi.mode(WIFI_MODE_AP);
    WiFi.softAP(AP_SSID, AP_PASS);
    Serial.println("\n[System] AP mode, IP: " + WiFi.softAPIP().toString());
  }

  startWebServerTask();
  Serial.println("[System] Web server started");

  vTaskDelete(NULL);
}
