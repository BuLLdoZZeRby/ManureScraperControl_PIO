#include "LoggerTask.h"
#include "Queues.h"
#include "FlashStorage.h"
#include <Arduino.h>

void LoggerTask(void* pv) {
  LogEntry e;
  for (;;) {
    if (xQueueReceive(logQueue, &e, portMAX_DELAY) == pdPASS) {
      String s = String(e.timestamp) + ": " + String(e.msg);
      FlashStorage::saveLog(s);
    }
  }
}
