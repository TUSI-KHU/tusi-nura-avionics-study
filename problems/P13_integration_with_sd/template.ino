// 시작 방법:
// 1) P10 answer.ino를 복사합니다.
// 2) 아래 TODO를 참고해 SD 로깅 기능을 추가합니다.

#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP085.h>

// 준비: P10의 상태/센서/전이 코드를 그대로 가져옵니다.

const int SD_CS_PIN = 10;
bool logEnabled = false;
unsigned long lastLogMs = 0;

void setupLogging() {
  // TODO 1: SD 초기화 + CSV 헤더 작성
  // TODO 1-1) SD 초기화 성공/실패를 판정하세요.
  // TODO 1-2) 실패하면 경고만 남기고 logEnabled=false로 유지하세요.
  // TODO 1-3) 성공하면 logEnabled=true로 두고 CSV 헤더를 작성하세요.
}

void logData(unsigned long now, const char* stateStr, float accMag, float relAlt) {
  // TODO 2: 100ms마다 CSV 한 줄 기록
  // TODO 2-1) logEnabled가 false면 즉시 반환하세요.
  // TODO 2-2) 100ms 주기 조건을 만족할 때만 기록하세요.
  // TODO 2-3) now,stateStr,accMag,relAlt 순서로 한 줄 작성하세요.
  // TODO 2-4) 쓰기 후 파일을 닫으세요.
  // TODO 2-5) 파일 열기 실패 시 상태머신은 계속 돌고 로그만 건너뛰게 하세요.
}

void setup() {
  // TODO 3: P10 setup + setupLogging()
  // TODO 3-1) P10 setup 내용을 먼저 유지하세요.
  // TODO 3-2) setup 마지막에 setupLogging()을 호출하세요.
}

void loop() {
  // TODO 4: P10 loop + logData()
  // TODO 4-1) P10 loop 호출 순서를 그대로 유지하세요.
  // TODO 4-2) 마지막에 현재 값으로 logData를 호출하세요.
  // TODO 4-3) SD 오류가 있어도 updateState/updateIndicators/printDebug는 계속 실행되게 하세요.
}
