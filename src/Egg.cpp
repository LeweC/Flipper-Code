#include <Arduino.h>
#include <DynamixelShield.h>
#include <sstream>
#include <string>  
#include <map>

const float DXL_PROTOCOL_VERSION = 2.0;

const int THUMB_ID = 2;
const int FINGER_ROTATE_ID = 1;
const int FINGER_EXTEND_ID = 3;

const float THUMB_THRESHOLD = 37;
const float FINGER_EXTEND_THRESHOLD = 2;
const float FINGER_ROTATE_THRESHOLD = 2;

DynamixelShield dxl;

int t;
std::map<int, float> homePositions;

void initializeMotor(int id);
void printStuff();
void run();
void home(int id, float threshold);
void move(int id, float threshold, float velocity);
void close(bool useThumb, float threshold);

void setup() {
    Serial.begin(57600);

    // Set Port baudrate to 57600bps. This has to match with DYNAMIXEL baudrate.
    dxl.begin(57600);
    // Set Port Protocol Version. This has to match with DYNAMIXEL protocol version.
    dxl.setPortProtocolVersion(DXL_PROTOCOL_VERSION);
    
    initializeMotor(1);
    initializeMotor(2);
    initializeMotor(3);

    run();
}

void loop() {}

void run() {
    // HACK
    Serial.print("hi");
    delay(5000);
    Serial.println("hi");
    
    home(THUMB_ID, THUMB_THRESHOLD);
    home(FINGER_EXTEND_ID, FINGER_EXTEND_THRESHOLD);
    home(FINGER_ROTATE_ID, FINGER_ROTATE_THRESHOLD);

    delay(1000);

    close(true, 20);

    Serial.println(homePositions[THUMB_ID]);
    Serial.println(homePositions[FINGER_EXTEND_ID]);
    Serial.println(homePositions[FINGER_ROTATE_ID]);
}

void home(int id, float threshold) {
    move(id, threshold, -100);
    Serial.print(id);
    Serial.println(" in home position");
}

void close(bool useThumb, float threshold) {
    if(useThumb) {
        dxl.setGoalPWM(THUMB_ID, 100);
    }
    dxl.setGoalPWM(FINGER_EXTEND_ID, 100);
    delay(100);
    while(dxl.getPresentVelocity(FINGER_EXTEND_ID) > threshold) {
        delay(1);
    }
    dxl.setGoalPWM(FINGER_EXTEND_ID, 0);
    dxl.setGoalPWM(THUMB_ID, 0);
    Serial.println("Closed");
}

void move(int id, float threshold, float velocity) {
    dxl.setGoalPWM(id, velocity);
    delay(100);
    while(dxl.getPresentVelocity(id) > threshold) {
        delay(1);
    }
    dxl.setGoalPWM(id, 0);
    homePositions[id] = dxl.getPresentPosition(id);
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
    float phi = (int) dxl.getPresentPosition(1, UNIT_DEGREE) % 360;
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
