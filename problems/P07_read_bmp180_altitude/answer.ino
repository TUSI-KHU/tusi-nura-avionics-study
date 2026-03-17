#include <Wire.h>
#include <Adafruit_BMP085.h>

Adafruit_BMP085 bmp;

bool calibrated = false;
float alt0 = 0;
float sumAlt = 0;
int sampleCount = 0;
unsigned long calibStartMs = 0;
unsigned long lastPrintMs = 0;

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
  float alt = bmp.readAltitude();
  unsigned long now = millis();

  if (!calibrated) {
    // 기준고도 평균 계산: 합계 / 샘플수
    sumAlt += alt;
    sampleCount++;
    if (now - calibStartMs >= 2000) {
      alt0 = sumAlt / sampleCount;
      calibrated = true;
      Serial.print("[OK] baseline alt0=");
      Serial.println(alt0);
    }
    return;
  }

  if (now - lastPrintMs >= 100) {
    lastPrintMs = now;
    // 상대고도 = 현재고도 - 기준고도
    float relAlt = alt - alt0;
    Serial.print("[BARO] alt=");
    Serial.print(alt);
    Serial.print(" alt0=");
    Serial.print(alt0);
    Serial.print(" relAlt=");
    Serial.println(relAlt);
  }
}
