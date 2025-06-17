#include "TelemetryTask.h"
#include <WiFi.h>
#include <HTTPClient.h>
#include "FlashStorage.h"

void TelemetryTask(void* pv) {
  const TickType_t interval = pdMS_TO_TICKS(60000);
  HTTPClient http;
  WiFiClient client;
  for (;;) {
    if (WiFi.status() == WL_CONNECTED) {
      String json = "{}";
      http.begin(client, "http://navoza.net/devices/api/device-data/");
      http.addHeader("Content-Type", "application/json");
      int code = http.POST(json);
      http.end();
      if (code < 200 || code >= 300) {
        FlashStorage::saveTelemetry(json);
      }
    }
    vTaskDelay(interval);
  }
}
