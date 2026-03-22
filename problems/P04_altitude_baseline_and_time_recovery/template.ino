#include <Wire.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP085.h>

enum State { BOOT, SAFE, ARMED, FLIGHT, RECOVERY };

Adafruit_MPU6050 mpu;
Adafruit_BMP085 bmp;
State state = BOOT;

float alt0 = 0;
float relAlt = 0;
unsigned long flightStartMs = 0;

void setState(State next, const char* reason) {
  state = next;
  if (next == FLIGHT) flightStartMs = millis();
  Serial.print("[STATE] reason=");
  Serial.println(reason);
}

void setup() {
  // TODO 1: P03 setup + bmp.begin() 추가
  // TODO 2: setup에서 alt0 평균값 계산
}

void loop() {
  unsigned long now = millis();

  // TODO 3: P03 loop 유지 + relAlt 계산/출력 추가

  // TODO 4: FLIGHT 시작 10초 뒤 RECOVERY(TIME)로 바꾸기
}
