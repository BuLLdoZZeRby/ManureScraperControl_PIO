#include "StateMachine.h"
#include <cstring>

StateMachine::StateMachine(){}

void StateMachine::update(const RegisterSnapshot& regs){}

Command StateMachine::nextCommand(){ return Command{0,0}; }

bool StateMachine::hasEvent() const { return false; }

StatusSnapshot StateMachine::snapshot() const {
  StatusSnapshot s;
  std::memset(s.regs, 0, sizeof(s.regs));
  s.state = 0;
  s.position = 0.0f;
  return s;
}
