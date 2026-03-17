#include <Wire.h>
#include <Adafruit_BMP085.h>

Adafruit_BMP085 bmp;

bool calibrated = false;
float alt0 = 0;
float sumAlt = 0;
int sampleCount = 0;
// 캘리브레이션 시작 시간을 저장합니다.
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
  // TODO 1: 시작 2초 동안 캘리브레이션(기준고도 평균)
  // STEP 1) 매 루프에서 현재 고도와 현재 시간을 읽으세요.
  // STEP 2) calibrated가 false인 동안 샘플을 누적하고 개수를 세세요.
  // STEP 3) 시작 후 2초가 지나면 평균값을 alt0로 저장하고 calibrated=true로 바꾸세요.
  // STEP 4) 캘리브레이션 중에는 상대고도 출력으로 내려가지 않도록 바로 return 하세요.

  // TODO 2: 캘리브레이션 완료 후 상대고도 출력
  // STEP 5) calibrated 이후에는 relAlt = 현재고도 - 기준고도로 계산하세요.
  // STEP 6) 출력은 100ms 주기로 제한하고 alt/alt0/relAlt를 함께 보여주세요.
}
