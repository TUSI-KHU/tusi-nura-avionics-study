// 시작 방법:
// 1) P10 answer.ino를 복사합니다.
// 2) 아래 TODO를 참고해 SD 로깅 기능을 추가합니다.

#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP085.h>

// TODO: P10의 상태/센서/전이 코드를 그대로 가져옵니다.

const int SD_CS_PIN = 10;
bool logEnabled = false;
unsigned long lastLogMs = 0;

void setupLogging() {
  // TODO 1: SD 초기화 + CSV 헤더 작성
}

void logData(unsigned long now, const char* stateStr, float accMag, float relAlt) {
  // TODO 2: 100ms마다 CSV 한 줄 기록
}

void setup() {
  // TODO 3: P10 setup + setupLogging()
}

void loop() {
  // TODO 4: P10 loop + logData()
}
