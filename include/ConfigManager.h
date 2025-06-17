#ifndef CONFIG_MANAGER_H
#define CONFIG_MANAGER_H
#include <Arduino.h>
#include <ArduinoJson.h>
#include "Types.h"

class ConfigManager {
public:
  static ConfigManager& get();
  void begin();
  void update(const JsonObject& cfg);
private:
  ConfigManager(){}
};

#endif