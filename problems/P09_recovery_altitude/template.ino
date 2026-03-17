#include <Wire.h>
#include <Adafruit_BMP085.h>

enum State { FLIGHT, RECOVERY };

Adafruit_BMP085 bmp;
State state = FLIGHT;

unsigned long flightStartMs = 0;
float alt0 = 0;
float maxRelAlt = 0;

void setState(State next, const char* reason) {
  state = next;
  Serial.print("[STATE] -> ");
  Serial.print(next == FLIGHT ? "FLIGHT" : "RECOVERY");
  Serial.print(" reason=");
  Serial.println(reason);
}

void setup() {
  Serial.begin(115200);
  Wire.begin();

  // TODO 1: BMP180 초기화
  // STEP 1) BMP180 begin 결과를 확인하고 실패 시 에러 출력 후 정지하세요.
  // TODO 2: alt0 기준고도 계산
  // STEP 2) 여러 샘플 평균으로 기준고도 alt0를 계산하세요.

  flightStartMs = millis();
}

void loop() {
  // TODO 3: relAlt 계산
  // STEP 3) relAlt는 현재 고도에서 alt0를 뺀 값으로 계산하세요.
  float relAlt = 0;

  // TODO 4: maxRelAlt 갱신
  // STEP 4) relAlt가 기존 최고값보다 크면 maxRelAlt를 갱신하세요.

  // TODO 5: 고도 조건으로 RECOVERY 전이
  // STEP 5) 최고점 대비 하강량이 5.0m를 넘으면 ALT reason으로 RECOVERY 전이하세요.
  // if (maxRelAlt - relAlt > 5.0) ...

  // TODO 6: 시간 백업 조건 유지
  // STEP 6) 고도 조건과 별개로 10초 시간 백업 전이를 함께 유지하세요.
}
