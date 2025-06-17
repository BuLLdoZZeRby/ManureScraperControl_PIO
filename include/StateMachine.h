#ifndef STATE_MACHINE_H
#define STATE_MACHINE_H
#include "Types.h"

class StateMachine {
public:
  StateMachine();
  void update(const RegisterSnapshot& regs);
  Command nextCommand();
  bool hasEvent() const;
  StatusSnapshot snapshot() const;
};

#endif