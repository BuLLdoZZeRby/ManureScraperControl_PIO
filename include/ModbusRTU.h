#ifndef MODBUS_RTU_H
#define MODBUS_RTU_H

#include <ModbusMaster.h>
#include <HardwareSerial.h>

class ModbusRTU {
public:
  ModbusRTU(uint8_t slaveId, HardwareSerial& serial);
  bool begin(uint32_t baudRate = 9600);
  bool readRegisters(uint16_t startReg, uint16_t count,
                     uint16_t* dest, uint8_t retries = 3);
  bool writeRegister(uint16_t reg, uint16_t value, uint8_t retries = 3);

private:
  ModbusMaster node;
  HardwareSerial& serialPort;
  uint8_t slaveId;
};

#endif // MODBUS_RTU_H
