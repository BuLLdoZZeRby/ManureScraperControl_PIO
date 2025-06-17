#include "ControlTask.h"
#include "Queues.h"
#include "StateMachine.h"

void ControlTask(void* pv) {
  StateMachine sm;
  RegisterSnapshot regs;
  Command cmd;
  for (;;) {
    if (xQueueReceive(regQueue, &regs, portMAX_DELAY) == pdPASS) {
      sm.update(regs);
      cmd = sm.nextCommand();
      if (cmd.addr) xQueueSend(cmdQueue, &cmd, 0);
      StatusSnapshot snap = sm.snapshot();
      xQueueOverwrite(stateQueue, &snap);
    }
  }
}
