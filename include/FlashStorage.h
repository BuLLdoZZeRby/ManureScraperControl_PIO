#ifndef FLASH_STORAGE_H
#define FLASH_STORAGE_H
#include <Arduino.h>
#include <vector>

class FlashStorage {
public:
  static void saveLog(const String& entry);
  static void saveTelemetry(const String& json);
  static std::vector<String> loadAllTelemetry();
  static void removeTelemetry(const String& json);
};

#endif