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
  // STEP 1) x/y/z 축 가속도 값을 지역변수로 분리하세요.
  // STEP 2) 벡터 크기 공식으로 mag를 계산하세요.
  // mag = sqrt(ax*ax + ay*ay + az*az)
  float mag = 0;

  // TODO 2: 임계치 비교 결과를 bool로 저장
  // STEP 3) mag가 임계치를 넘는지 bool 결과로 저장하세요.
  // bool isEvent = (mag > THRESHOLD);

  // TODO 3: 50ms 주기로 mag와 isEvent 출력
  // STEP 4) 50ms 주기로 제한해서 mag와 이벤트 판정을 함께 출력하세요.
}
