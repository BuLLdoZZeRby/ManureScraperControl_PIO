#include <Arduino.h>
#include "Queues.h"
#include "Types.h"
#include "ModbusRTU.h"
#include "ModbusTask.h"
#include "ControlTask.h"
#include "PositionTask.h"
#include "LoggerTask.h"
#include "SystemTask.h"
#include "TelemetryTask.h"
#include "OTATask.h"
#include "WebServerTask.h"

#define MODBUS_BAUD 9600

const char* SSID     = "forall";
const char* PASSWORD = "6011898qw";
const char* AP_SSID  = "ScraperAP";
const char* AP_PASS  = "ap_password";

// FreeRTOS queues
QueueHandle_t regQueue, cmdQueue, logQueue, stateQueue, positionQueue;

void setup() {
  // Debug Serial
  Serial.begin(115200);
  Serial.println("[Setup] Starting ManureScraperControl");

  // Init Serial1 for Modbus
  // Initialize Serial1 for Modbus (UART1) on GPIO16/17
  Serial1.begin(MODBUS_BAUD, SERIAL_8N1, 16, 17);
  Serial.println("[Setup] Serial1 for Modbus initialized");

  // Create queues
  regQueue      = xQueueCreate(1, sizeof(RegisterSnapshot));
  cmdQueue      = xQueueCreate(5, sizeof(Command));
  logQueue      = xQueueCreate(20, sizeof(LogEntry));
  stateQueue    = xQueueCreate(1, sizeof(StatusSnapshot));
  positionQueue = xQueueCreate(1, sizeof(float));

  // Core 1 tasks
  xTaskCreatePinnedToCore(ModbusTask,   "Modbus",   4096, NULL, PRIO_MODBUS, NULL, 1);
  xTaskCreatePinnedToCore(ControlTask,  "Control",  4096, NULL, PRIO_CONTROL, NULL, 1);
  xTaskCreatePinnedToCore(PositionTask, "Position", 2048, NULL, PRIO_POSITION, NULL, 1);
  xTaskCreatePinnedToCore(LoggerTask,   "Logger",   2048, NULL, PRIO_LOGGER, NULL, 1);

  // Core 0 tasks
  xTaskCreatePinnedToCore(SystemTask,    "System",    4096, NULL, 1,    NULL, 0);
  xTaskCreatePinnedToCore(TelemetryTask, "Telemetry", 4096, NULL, PRIO_TELEMETRY, NULL, 0);
  xTaskCreatePinnedToCore(OTATask,       "OTA",       4096, NULL, PRIO_OTA,       NULL, 0);
}

void loop() {
  // All work in tasks
}
