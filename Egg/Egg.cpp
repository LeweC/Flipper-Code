#include <Arduino.h>
#include <DynamixelShield.h>

const float DXL_PROTOCOL_VERSION = 2.0;

DynamixelShield dxl;

void setup() {
  // Set Port baudrate to 57600bps. This has to match with DYNAMIXEL baudrate.
  dxl.begin(57600);
  // Set Port Protocol Version. This has to match with DYNAMIXEL protocol version.
  dxl.setPortProtocolVersion(DXL_PROTOCOL_VERSION);
  // Get DYNAMIXEL information (???)
  dxl.ping(1);
  dxl.ping(2);
  dxl.ping(3);

  // Turn off torque when configuring items in EEPROM area
  dxl.torqueOff(1);
  dxl.setOperatingMode(1, OP_POSITION);
  dxl.torqueOn(1);
  dxl.torqueOff(2);
  dxl.setOperatingMode(2, OP_POSITION);
  dxl.torqueOn(2);
  dxl.torqueOff(3);
  dxl.setOperatingMode(3, OP_POSITION);
  dxl.torqueOn(3);
}

void loop() {
  dxl.setGoalPosition(1, 512);
  dxl.setGoalPosition(2, 512);
  dxl.setGoalPosition(3, 512);
  delay(1000);
  dxl.setGoalPosition(1, 0);
  dxl.setGoalPosition(2, 0);
  dxl.setGoalPosition(3, 0);
  delay(1000);
}
