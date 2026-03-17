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

  if (!bmp.begin()) {
    Serial.println("[ERR] BMP180 init failed");
    while (1) delay(1000);
  }

  float sum = 0;
  for (int i = 0; i < 20; i++) {
    sum += bmp.readAltitude();
    delay(30);
  }
  alt0 = sum / 20.0;

  flightStartMs = millis();
}

void loop() {
  if (state != FLIGHT) return;

  float relAlt = bmp.readAltitude() - alt0;
  if (relAlt > maxRelAlt) maxRelAlt = relAlt;

  if (maxRelAlt - relAlt > 5.0) {
    setState(RECOVERY, "ALT");
    return;
  }

  if (millis() - flightStartMs > 10000) {
    setState(RECOVERY, "TIME");
    return;
  }

  Serial.print("[FLIGHT] relAlt=");
  Serial.print(relAlt);
  Serial.print(" maxRelAlt=");
  Serial.println(maxRelAlt);
  delay(100);
}
