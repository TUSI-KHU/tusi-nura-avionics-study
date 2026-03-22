#include <Wire.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP085.h>

enum State { BOOT, SAFE, ARMED, FLIGHT, RECOVERY };

State state = BOOT;
unsigned long stateStartMs = 0;
unsigned long flightStartMs = 0;
unsigned long launchStartMs = 0;
unsigned long lastDebugMs = 0;

float accMag = 0;
float relAlt = 0;
float alt0 = 0;

void setState(State next, const char* reason);
void updateInput(unsigned long now);
void updateSensors(unsigned long now);
void updateState(unsigned long now);
void printDebug(unsigned long now);

void setup() {
  // TODO 1: P04 setup 코드 하나로 합치기
}

void loop() {
  unsigned long now = millis();
  updateInput(now);
  updateSensors(now);
  updateState(now);
  printDebug(now);
}

void setState(State next, const char* reason) {
  // TODO 2: 상태 바꾸는 공통 함수
  // - state/stateStartMs 업데이트
  // - FLIGHT로 바뀔 때 flightStartMs 설정
  // - reason 로그 출력
}

void updateInput(unsigned long now) {
  // TODO 3: SAFE/ARMED 버튼 동작
}

void updateSensors(unsigned long now) {
  // TODO 4: IMU accMag, BARO relAlt 값 업데이트
}

void updateState(unsigned long now) {
  // TODO 5: BOOT->SAFE, ARMED->FLIGHT 상태 바꾸기
  // TODO 6: FLIGHT->RECOVERY (TIME만 사용)
}

void printDebug(unsigned long now) {
  if (now - lastDebugMs < 100) return;
  lastDebugMs = now;
  // TODO 7: state, accMag, relAlt 출력
}
