#include <SPI.h>
#include <SD.h>

const int SD_CS_PIN = 10;

void setup() {
  Serial.begin(115200);

  if (!SD.begin(SD_CS_PIN)) {
    Serial.println("[ERR] SD init failed");
    return;
  }

  File f = SD.open("test.txt", FILE_WRITE);
  if (!f) {
    Serial.println("[ERR] open test.txt failed");
    return;
  }

  f.println("sd basic check ok");
  f.close();
  Serial.println("[OK] SD basic check done");
}

void loop() {
}
