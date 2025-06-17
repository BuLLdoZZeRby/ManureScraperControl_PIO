#include "ModbusRTU.h"

ModbusRTU::ModbusRTU(uint8_t _slaveId, HardwareSerial& serial)
  : node(), serialPort(serial), slaveId(_slaveId) {}

bool ModbusRTU::begin(uint32_t baudRate) {
  serialPort.begin(baudRate, SERIAL_8N1);
  node.begin(slaveId, serialPort);
  return true;
}

bool ModbusRTU::readRegisters(uint16_t startReg, uint16_t count,
                              uint16_t* dest, uint8_t retries) {
  for (uint8_t i = 0; i < retries; ++i) {
    uint8_t rc = node.readHoldingRegisters(startReg, count);
    if (rc == node.ku8MBSuccess) {
      for (uint16_t j = 0; j < count; ++j) {
        dest[j] = node.getResponseBuffer(j);
      }
      return true;
    }
    delay(10);
  }
  return false;
}

bool ModbusRTU::writeRegister(uint16_t reg, uint16_t value, uint8_t retries) {
  for (uint8_t i = 0; i < retries; ++i) {
    uint8_t rc = node.writeSingleRegister(reg, value);
    if (rc == node.ku8MBSuccess) return true;
    delay(10);
  }
  return false;
}
