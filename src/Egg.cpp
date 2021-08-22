#include <Arduino.h>
#include <DynamixelShield.h>

const float DXL_PROTOCOL_VERSION = 2.0;

DynamixelShield dxl;

void initializeMotor(int id);

void setup() {
    Serial.begin(57600);

    // Set Port baudrate to 57600bps. This has to match with DYNAMIXEL baudrate.
    dxl.begin(57600);
    // Set Port Protocol Version. This has to match with DYNAMIXEL protocol version.
    dxl.setPortProtocolVersion(DXL_PROTOCOL_VERSION);
    
    initializeMotor(1);
    initializeMotor(2);
    initializeMotor(3);
    
    Serial.println("hello world");
}

void loop() {
    Serial.println("hello world!!!1");
    dxl.setGoalPosition(1, 512);
    // dxl.setGoalPosition(2, 512);
    // dxl.setGoalPosition(3, 512);
    delay(1000);
    dxl.setGoalPosition(1, 0);
    // dxl.setGoalPosition(2, 0);
    // dxl.setGoalPosition(3, 0);
    delay(1000);
}

void initializeMotor(int id) {
    // Get DYNAMIXEL information
    dxl.ping(id);

    // Turn off torque when configuring items in EEPROM area
    dxl.torqueOff(id);
    dxl.setOperatingMode(id, OP_POSITION);
    dxl.torqueOn(id);
}
