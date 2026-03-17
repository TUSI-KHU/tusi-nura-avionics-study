#include <SPI.h>
#include <SD.h>

const int SD_CS_PIN = 10;
bool logEnabled = false;
unsigned long lastLogMs = 0;

void setup() {
  Serial.begin(115200);

  if (!SD.begin(SD_CS_PIN)) {
    Serial.println("[WARN] SD init failed. Logging disabled.");
    return;
  }

  logEnabled = true;
  File f = SD.open("flight.csv", FILE_WRITE);
  if (f) {
    f.println("millis,state,accMag,relAlt");
    f.close();
    Serial.println("[OK] CSV header written");
  } else {
    Serial.println("[WARN] Failed to open flight.csv");
    logEnabled = false;
  }
}

void loop() {
  unsigned long t = millis();
  const char* state = "SAFE";
  float accMag = 9.8;
  float relAlt = 0.0;

  if (logEnabled && t - lastLogMs >= 100) {
    lastLogMs = t;
    File f = SD.open("flight.csv", FILE_WRITE);
    if (f) {
      f.print(t);
      f.print(',');
      f.print(state);
      f.print(',');
      f.print(accMag, 2);
      f.print(',');
      f.println(relAlt, 2);
      f.close();
    }
  }
}
