#include <Wire.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>

enum State { BOOT, SAFE, ARMED, FLIGHT };

const float THRESHOLD = 17.5;
const unsigned long HOLD_MS = 150;

State state = BOOT;
Adafruit_MPU6050 mpu;

float ax = 0, ay = 0, az = 0;
float accMag = 0;
unsigned long launchStartMs = 0;
unsigned long stateStartMs = 0;

void setState(State next, const char* reason) {
  state = next;
  stateStartMs = millis();
  Serial.print("[STATE] -> ");
  Serial.print((next == FLIGHT) ? "FLIGHT" : "OTHER");
  Serial.print(" reason=");
  Serial.println(reason);
}

void setup() {
  // TODO 1: P02 setup/초기화 코드 가져오기
}

void loop() {
  unsigned long now = millis();

  // TODO 2: P02의 상태/버튼/IMU/디버그 흐름 그대로 유지

  // TODO 3: ARMED에서 발사 조건 확인
  // - accMag 계산
  // - accMag > THRESHOLD면 타이머 시작/유지
  // - HOLD_MS를 채우면 setState(FLIGHT, "IMU_HOLD")
  // - 조건이 깨지면 launchStartMs=0
}
