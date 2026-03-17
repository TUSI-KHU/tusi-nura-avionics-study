#include <SPI.h>
#include <SD.h>

const int SD_CS_PIN = 10;

void setup() {
  Serial.begin(115200);

  // TODO 1: SD.begin(SD_CS_PIN) 초기화
  // TODO 2: test.txt에 한 줄 쓰기
  // TODO 3: 성공/실패 로그 출력
}

void loop() {
}
