#ifndef STATE_MACHINE_H
#define STATE_MACHINE_H
#include "Types.h"

enum class AutoState {
  IDLE,
  MOVE_BACK,
  WAIT_AFTER_RESET1,
  MOVE_FORWARD,
  WAIT_AFTER_RESET2,
  MOVE_BACK_FINAL,
  PAUSE
};

class StateMachine {
public:
  StateMachine();
  void update(const RegisterSnapshot& regs);
  Command nextCommand();
  bool hasEvent() const;
  StatusSnapshot snapshot() const;

  private:
  RegisterSnapshot currentRegs;
  AutoState        autoState;
  bool             autoMode;
  bool             firstCycle;
  uint32_t         stateTimestamp;
  Command          pending;
  uint16_t         controlValue;
};

#endif