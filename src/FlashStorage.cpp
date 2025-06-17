#include "FlashStorage.h"
#include <SPIFFS.h>

void FlashStorage::saveLog(const String& entry){}
void FlashStorage::saveTelemetry(const String& json){}
std::vector<String> FlashStorage::loadAllTelemetry(){ return {}; }
void FlashStorage::removeTelemetry(const String& json){}
