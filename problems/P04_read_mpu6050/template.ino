#include <Wire.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>

Adafruit_MPU6050 mpu;
unsigned long lastPrintMs = 0;

void setup() {
  Serial.begin(115200);
  Wire.begin();

  // TODO 1: MPU6050 초기화
  // STEP 1) 센서 begin 호출로 초기화 성공/실패를 판정하세요.
  // TODO 2: 초기화 실패 시 에러 처리
  // STEP 2) 실패 시 에러를 출력하고 루프를 멈춰 오동작을 막으세요.
  // STEP 3) 성공 시 확인 로그를 1회 출력하세요.
}

void loop() {
  // TODO 3: sensors_event_t로 가속도 읽고 50ms마다 출력
  // STEP 4) 이벤트 구조체를 만들고 getEvent로 최신 값을 읽으세요.
  // STEP 5) millis() 기반 50ms 주기를 적용해 시리얼 출력량을 제한하세요.
  // STEP 6) 출력 항목은 ax, ay, az 3축 값을 모두 포함하세요.
  // 참고:
  // - a.acceleration.x, y, z 단위는 m/s^2 입니다.
  // - 출력 주기 제어는 millis()를 사용합니다.
}
