#include "StateMachine.h"
#include <Arduino.h>
#include <cstring>

StateMachine::StateMachine()
    : currentRegs{}, autoState(AutoState::IDLE), autoMode(false),
      firstCycle(true), stateTimestamp(0), pending{0, 0}, controlValue(0) {}

void StateMachine::update(const RegisterSnapshot& regs) {
  currentRegs = regs;
  bool newAuto = (regs.regs[2] == regs.regs[7]);
  uint32_t now = millis();

  uint16_t desiredControl = newAuto ? 2 : regs.regs[4];
  if (desiredControl != controlValue) {
    pending = {1, desiredControl};
    controlValue = desiredControl;
  }

  if (!newAuto) {
    autoMode = false;
    autoState = AutoState::IDLE;
    if (regs.regs[1] == 4) {
      pending = {4096, 7};
    }
    return;
  }

  if (!autoMode) {
    autoMode = true;
    autoState = firstCycle ? AutoState::MOVE_BACK : AutoState::MOVE_FORWARD;
    stateTimestamp = now;
  }

  switch (autoState) {
  case AutoState::MOVE_BACK:
    if (pending.addr == 0) {
      pending = {4096, 2};
    }
    if (regs.regs[1] == 4) {
      pending = {4096, 7};
      autoState = AutoState::WAIT_AFTER_RESET1;
      stateTimestamp = now;
    }
    break;
  case AutoState::WAIT_AFTER_RESET1:
    if (now - stateTimestamp >= 5000) {
      pending = {4096, 1};
      autoState = AutoState::MOVE_FORWARD;
    }
    break;
  case AutoState::MOVE_FORWARD:
    if (regs.regs[1] == 4) {
      pending = {4096, 7};
      autoState = AutoState::WAIT_AFTER_RESET2;
      stateTimestamp = now;
    }
    break;
  case AutoState::WAIT_AFTER_RESET2:
    if (now - stateTimestamp >= 5000) {
      pending = {4096, 2};
      autoState = AutoState::MOVE_BACK_FINAL;
    }
    break;
  case AutoState::MOVE_BACK_FINAL:
    if (regs.regs[1] == 4) {
      pending = {4096, 7};
      autoState = AutoState::PAUSE;
      stateTimestamp = now;
      firstCycle = false;
    }
    break;
  case AutoState::PAUSE:
    if (now - stateTimestamp >= ((uint32_t)regs.regs[6]) * 60000UL) {
      autoState = AutoState::MOVE_FORWARD;
    }
    break;
  default:
    break;
  }
}

Command StateMachine::nextCommand() {
  Command c = pending;
  pending = {0, 0};
  return c;
}
bool StateMachine::hasEvent() const { return false; }

StatusSnapshot StateMachine::snapshot() const {
  StatusSnapshot s;
  memcpy(s.regs, currentRegs.regs, sizeof(currentRegs.regs));
  s.state = static_cast<uint8_t>(autoState);
  s.position = 0.0f;
  return s;
}
