#include <SPI.h>
#include <SD.h>

const int SD_CS_PIN = 10;
bool logEnabled = false;
unsigned long lastLogMs = 0;

void setup() {
  Serial.begin(115200);

  // TODO 1: SD 초기화
  // TODO 2: flight.csv 헤더 작성
}

void loop() {
  unsigned long t = millis();
  const char* state = "SAFE";
  float accMag = 9.8;
  float relAlt = 0.0;

  // TODO 3: 100ms마다 CSV 한 줄 기록
}
