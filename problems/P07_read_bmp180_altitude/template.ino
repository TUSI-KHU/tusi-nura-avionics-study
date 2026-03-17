#include <Wire.h>
#include <Adafruit_BMP085.h>

Adafruit_BMP085 bmp;

bool calibrated = false;
float alt0 = 0;
float sumAlt = 0;
int sampleCount = 0;
// 캘리브레이션 시작 시간을 저장합니다.
unsigned long calibStartMs = 0;

void setup() {
  Serial.begin(115200);
  Wire.begin();
  if (!bmp.begin()) {
    Serial.println("[ERR] BMP180 init failed");
    while (1) delay(1000);
  }
  calibStartMs = millis();
}

void loop() {
  // TODO 1: 시작 2초 동안 캘리브레이션(기준고도 평균)
  // TODO 2: 캘리브레이션 완료 후 상대고도 출력
}
