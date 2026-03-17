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

  float ax = a.acceleration.x;
  float ay = a.acceleration.y;
  float az = a.acceleration.z;
  // sqrt는 제곱근 함수, float 계산 결과를 반환
  float mag = sqrt(ax * ax + ay * ay + az * az);

  bool isEvent = (mag > THRESHOLD);

  unsigned long now = millis();
  if (now - lastPrintMs >= 50) {
    lastPrintMs = now;
    Serial.print("[IMU] mag=");
    Serial.print(mag);
    Serial.print(" event=");
    Serial.println(isEvent ? 1 : 0);
  }
}
