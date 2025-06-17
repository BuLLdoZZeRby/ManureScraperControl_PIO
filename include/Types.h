#pragma once
#include <Arduino.h>

enum TaskPriority {
  PRIO_MODBUS    = 5,
  PRIO_CONTROL   = 5,
  PRIO_POSITION  = 3,
  PRIO_LOGGER    = 3,
  PRIO_WEBSERVER = 1,
  PRIO_TELEMETRY = 1,
  PRIO_OTA       = 1
};

struct RegisterSnapshot {
  uint16_t regs[12];
};

struct Command {
  uint16_t addr;
  uint16_t value;
};

struct LogEntry {
  uint32_t timestamp;
  char     msg[64];
};

struct StatusSnapshot {
  uint16_t regs[12];
  uint8_t  state;
  float    position;
};
