#include "ConfigManager.h"
ConfigManager& ConfigManager::get() {
  static ConfigManager instance;
  return instance;
}
void ConfigManager::begin(){}
void ConfigManager::update(const JsonObject& cfg){}
