#include <Wire.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>

enum State { BOOT, SAFE, ARMED };

const int LED_PIN = 8;
const int BUTTON_PIN = 4;
const int BUZZER_PIN = 9;

State state = BOOT;
Adafruit_MPU6050 mpu;

float ax = 0, ay = 0, az = 0;
unsigned long stateStartMs = 0;
unsigned long lastImuMs = 0;
unsigned long lastDebugMs = 0;

void setState(State next);
void updateButton(unsigned long now);
void updateImu(unsigned long now);
void printDebug(unsigned long now);

void setup() {
  // TODO A1: P01의 setup 코드 가져오기(핀 설정 + 시작 상태)

  Serial.begin(115200);
  Wire.begin();

  // TODO A2: mpu.begin() 확인
  // - 실패하면 [ERR] 출력하고 멈추기
}

void loop() {
  unsigned long now = millis();

  // TODO B: P01의 BOOT/버튼/LED 동작 그대로 넣기

  updateImu(now);
  printDebug(now);
}

void setState(State next) {
  state = next;
  stateStartMs = millis();
}

void updateButton(unsigned long now) {
  // TODO C1: P01 버튼 길게 누르기 코드 복사
}

void updateImu(unsigned long now) {
  if (now - lastImuMs < 50) return;
  lastImuMs = now;

  // TODO C2: mpu.getEvent()로 ax/ay/az 값 업데이트
}

const char* stateToStr(State s) {
  if (s == BOOT) return "BOOT";
  if (s == SAFE) return "SAFE";
  return "ARMED";
}

void printDebug(unsigned long now) {
  if (now - lastDebugMs < 100) return;
  lastDebugMs = now;

  // TODO C3: 안내된 형식으로 디버그 출력
}
