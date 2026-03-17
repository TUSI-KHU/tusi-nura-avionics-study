#include <SPI.h>
#include <SD.h>

const int SD_CS_PIN = 10;
bool logEnabled = false;
unsigned long lastLogMs = 0;

void setup() {
  Serial.begin(115200);

  // TODO 1: SD 초기화
  // STEP 1) SD begin 결과에 따라 logEnabled를 켜거나 끄세요.
  // STEP 2) 실패 시 경고를 출력하고 로깅만 비활성화하세요.

  // TODO 2: flight.csv 헤더 작성
  // STEP 3) setup에서 헤더를 1회만 작성하세요.
}

void loop() {
  unsigned long t = millis();
  const char* state = "SAFE";
  float accMag = 9.8;
  float relAlt = 0.0;

  // TODO 3: 100ms마다 CSV 한 줄 기록
  // STEP 4) logEnabled가 true이고 100ms가 지났을 때만 기록하세요.
  // STEP 5) 컬럼 순서는 millis,state,accMag,relAlt를 유지하세요.
  // STEP 6) 매 기록 후 파일을 닫아 데이터 유실을 줄이세요.
}
