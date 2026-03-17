#include <Wire.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP085.h>

enum State { BOOT, SAFE, ARMED, FLIGHT, RECOVERY };

const int LED_PIN = 8;
const int BUTTON_PIN = 4;
const int BUZZER_PIN = 9;

State state = BOOT;
unsigned long stateEnterMs = 0;

Adafruit_MPU6050 mpu;
Adafruit_BMP085 bmp;

bool imuOk = false;
bool baroOk = false;

float accMag = 0;
float relAlt = 0;
float alt0 = 0;
float maxRelAlt = 0;

void setState(State next, const char* reason);
void updateButton();
void readIMU();
void readBarometer();
void updateState();
void updateIndicators();
void printDebug();

void setup() {
  // TODO: 핀/시리얼/센서 초기화
}

void loop() {
  updateButton();
  readIMU();
  readBarometer();
  updateState();
  updateIndicators();
  printDebug();
}

void setState(State next, const char* reason) {
  // TODO
}

void updateButton() {
  // TODO
}

void readIMU() {
  // TODO
}

void readBarometer() {
  // TODO
}

void updateState() {
  // TODO
}

void updateIndicators() {
  // TODO
}

void printDebug() {
  // TODO
}
