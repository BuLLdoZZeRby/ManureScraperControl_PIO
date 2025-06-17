#include "WebServerTask.h"
#include <SPIFFS.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <ArduinoJson.h>

static AsyncWebServer server(80);
static AsyncWebSocket ws("/ws");

void startWebServerTask(){
  if (!SPIFFS.begin(true)) return;
  server.serveStatic("/", SPIFFS, "/html/").setDefaultFile("index.html");
  server.addHandler(&ws);
  server.begin();
}
