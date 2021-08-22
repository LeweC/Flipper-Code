#include <Arduino.h>
#include <DynamixelShield.h>
#include <sstream>
#include <string>  

const float DXL_PROTOCOL_VERSION = 2.0;

DynamixelShield dxl;

int t;

void initializeMotor(int id);
void wobble();
void printStuff();

void setup() {
    Serial.begin(57600);

    // Set Port baudrate to 57600bps. This has to match with DYNAMIXEL baudrate.
    dxl.begin(57600);
    // Set Port Protocol Version. This has to match with DYNAMIXEL protocol version.
    dxl.setPortProtocolVersion(DXL_PROTOCOL_VERSION);
    
    initializeMotor(1);
    initializeMotor(2);
    initializeMotor(3);

    // wobble();
}

void loop() {
    printStuff();
    dxl.setGoalPWM(1, 200);
    t += 100;

    delay(100);
}

void initializeMotor(int id) {
    // Get DYNAMIXEL information
    dxl.ping(id);

    // Turn off torque when configuring items in EEPROM area
    dxl.torqueOff(id);
    dxl.setOperatingMode(id, OP_PWM);
    dxl.torqueOn(id);
}

void printStuff() {
    float i = dxl.getPresentCurrent(1);
    float phi = dxl.getPresentPosition(1);
    float pwm = dxl.getPresentPWM(1);
    float phidot = dxl.getPresentVelocity(1);

    // TODO: string format
    Serial.print("i: ");
    Serial.print(i);
    Serial.print("\tphi: ");
    Serial.print(phi);
    Serial.print("\tpwm: ");
    Serial.print(pwm);
    Serial.print("\tphidot: ");
    Serial.println(phidot);
}
