#include <SPI.h>
#include <SD.h>

const int SD_CS_PIN = 10;
bool logEnabled = false;
unsigned long lastLogMs = 0;

// TODO 1: P06의 상태/센서/상태변경 코드를 먼저 붙여넣으세요.

void setupLogging() {
  // TODO 2:
  // - SD.begin(SD_CS_PIN) 확인
  // - 성공하면 flight.csv 헤더 쓰기
  // - 실패하면 logEnabled=false 유지
}

void logData(unsigned long now) {
  // TODO 3:
  // - logEnabled=false면 바로 return
  // - 100ms마다만 기록
  // - now,state,accMag,relAlt를 한 줄로 저장
  // - 파일 열기/쓰기 실패는 경고만 출력
}

void setup() {
  // TODO 4: P06 setup 마지막에서 setupLogging() 호출
}

void loop() {
  // TODO 5: P06 loop 마지막에서 logData() 호출
}
