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
  // TODO 2: alt0 기준고도 계산

  flightStartMs = millis();
}

void loop() {
  // TODO 3: relAlt 계산
  float relAlt = 0;

  // TODO 4: maxRelAlt 갱신

  // TODO 5: 고도 조건으로 RECOVERY 전이
  // if (maxRelAlt - relAlt > 5.0) ...

  // TODO 6: 시간 백업 조건 유지
}
