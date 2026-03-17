#include <Wire.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>

Adafruit_MPU6050 mpu;
unsigned long lastPrintMs = 0;

void setup() {
  Serial.begin(115200);
  Wire.begin();

  // TODO 1: MPU6050 초기화
  // TODO 2: 초기화 실패 시 에러 처리
}

void loop() {
  // TODO 3: sensors_event_t로 가속도 읽고 50ms마다 출력
  // 참고:
  // - a.acceleration.x, y, z 단위는 m/s^2 입니다.
  // - 출력 주기 제어는 millis()를 사용합니다.
}
