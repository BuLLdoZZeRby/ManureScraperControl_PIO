#include "OTATask.h"
#include <WiFi.h>
#include <HTTPClient.h>
#include <HTTPUpdate.h>

void OTATask(void* pv) {
  for (;;) {
    if (WiFi.status() == WL_CONNECTED) {
      HTTPClient http;
      WiFiClient client;
      http.begin(client, "http://navoza.net/firmware/check/2345618/");
      int code = http.GET();
      http.end();
    }
    vTaskDelay(pdMS_TO_TICKS(3600000));
  }
}
