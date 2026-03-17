#include <Wire.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>

Adafruit_MPU6050 mpu;

const float THRESHOLD = 17.5;

unsigned long lastPrintMs = 0;

void setup() {
  Serial.begin(115200);
  Wire.begin();
  if (!mpu.begin()) {
    Serial.println("[ERR] MPU init failed");
    while (1) delay(1000);
  }
}

void loop() {
  sensors_event_t a, g, t;
  mpu.getEvent(&a, &g, &t);

  // TODO 1: 가속도 크기(magnitude) 계산
  // mag = sqrt(ax*ax + ay*ay + az*az)
  float mag = 0;

  // TODO 2: 임계치 비교 결과를 bool로 저장
  // bool isEvent = (mag > THRESHOLD);

  // TODO 3: 50ms 주기로 mag와 isEvent 출력
}
