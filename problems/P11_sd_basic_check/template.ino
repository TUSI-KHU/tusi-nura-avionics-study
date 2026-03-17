#include <SPI.h>
#include <SD.h>

const int SD_CS_PIN = 10;

void setup() {
  Serial.begin(115200);

  // TODO 1: SD.begin(SD_CS_PIN) 초기화
  // STEP 1) SD 초기화 성공/실패를 먼저 판정하고 실패 시 즉시 종료하세요.

  // TODO 2: test.txt에 한 줄 쓰기
  // STEP 2) 파일 열기 -> 한 줄 기록 -> 닫기 순서로 처리하세요.
  // STEP 3) 파일 열기 실패 시 에러를 출력하고 종료하세요.

  // TODO 3: 성공/실패 로그 출력
  // STEP 4) 성공 시 [OK], 실패 시 [ERR] 형식으로 명확히 출력하세요.
}

void loop() {
}
