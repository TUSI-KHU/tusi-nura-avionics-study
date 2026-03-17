#include <Wire.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>

Adafruit_MPU6050 mpu;
unsigned long lastPrintMs = 0;

void setup() {
  Serial.begin(115200);
  Wire.begin();

  // ! 연산자는 논리 부정(not) 입니다.
  if (!mpu.begin()) {
    Serial.println("[ERR] MPU6050 init failed");
    // while(1): 무한 루프. 치명적 초기화 실패 시 정지 용도로 자주 사용
    while (1) {
      delay(1000);
    }
  }

  Serial.println("[OK] MPU6050 init success");
}

void loop() {
  sensors_event_t a, g, temp;
  // getEvent(&a, &g, &temp): 구조체 주소를 넘겨 함수가 값을 채웁니다.
  mpu.getEvent(&a, &g, &temp);

  unsigned long now = millis();
  if (now - lastPrintMs >= 50) {
    // 50ms마다 한 번만 출력해서 시리얼 폭주를 막습니다.
    lastPrintMs = now;
    Serial.print("[IMU] ax=");
    Serial.print(a.acceleration.x);
    Serial.print(" ay=");
    Serial.print(a.acceleration.y);
    Serial.print(" az=");
    Serial.println(a.acceleration.z);
  }
}
