#include "ModbusTask.h"
#include "ModbusRTU.h"
#include "Queues.h"
#include <Arduino.h>

#define REG(r) ((r) - 1)
static ModbusRTU modbus(1, Serial1);

void ModbusTask(void* pv) {
  Serial.println("[ModbusTask] start");
  modbus.begin(9600);

  RegisterSnapshot snapshot;
  Command cmd;

  for (;;) {
    bool ok1 = modbus.readRegisters(REG(1), 1, &snapshot.regs[0]);
    bool ok2 = modbus.readRegisters(REG(4097), 1, &snapshot.regs[1]);

    uint16_t buf2[2];
    bool ok3 = modbus.readRegisters(REG(12289), 2, buf2);
    snapshot.regs[2] = buf2[0];
    snapshot.regs[3] = buf2[1];

    uint16_t buf6[6];
    bool ok4 = modbus.readRegisters(REG(2601), 6, buf6);
    memcpy(&snapshot.regs[4], buf6, 6 * sizeof(uint16_t));

    if (!(ok1 && ok2 && ok3 && ok4)) {
      Serial.println("[ModbusTask] ERROR reading regs");
    } else {
      xQueueOverwrite(regQueue, &snapshot);
    }

    if (xQueueReceive(cmdQueue, &cmd, 0) == pdPASS) {
      modbus.writeRegister(REG(cmd.addr), cmd.value);
    }

    vTaskDelay(pdMS_TO_TICKS(1000));
  }
}
