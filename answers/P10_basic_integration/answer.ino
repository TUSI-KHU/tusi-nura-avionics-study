#include <Wire.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP085.h>

enum State { BOOT, SAFE, ARMED, FLIGHT, RECOVERY };

const int LED_PIN = 8;
const int BUTTON_PIN = 4;
const int BUZZER_PIN = 9;

const unsigned long BOOT_MS = 3000;
const float LAUNCH_THR = 17.5;
const unsigned long LAUNCH_HOLD_MS = 150;
const float RECOVERY_DROP_M = 5.0;
const unsigned long RECOVERY_TIMEOUT_MS = 10000;

State state = BOOT;
unsigned long stateEnterMs = 0;
unsigned long flightStartMs = 0;
unsigned long launchCondStartMs = 0;

Adafruit_MPU6050 mpu;
Adafruit_BMP085 bmp;

bool imuOk = false;
bool baroOk = false;

float accMag = 9.8;
float relAlt = 0;
float alt0 = 0;
float maxRelAlt = 0;

int lastBtn = HIGH;
unsigned long lastDebugMs = 0;
unsigned long lastBlinkMs = 0;
bool ledOn = false;

const char* stateToStr(State s) {
  if (s == BOOT) return "BOOT";
  if (s == SAFE) return "SAFE";
  if (s == ARMED) return "ARMED";
  if (s == FLIGHT) return "FLIGHT";
  return "RECOVERY";
}

void setState(State next, const char* reason) {
  state = next;
  stateEnterMs = millis();
  Serial.print("[STATE] ");
  Serial.print(stateToStr(state));
  Serial.print(" reason=");
  Serial.println(reason);

  if (state == FLIGHT) {
    flightStartMs = millis();
    maxRelAlt = relAlt;
  }
}

void updateButton() {
  int btn = digitalRead(BUTTON_PIN);
  if (lastBtn == HIGH && btn == LOW) {
    if (state == SAFE) setState(ARMED, "BUTTON");
    else if (state == ARMED) setState(SAFE, "BUTTON");
  }
  lastBtn = btn;
}

void readIMU() {
  if (!imuOk) return;
  sensors_event_t a, g, t;
  mpu.getEvent(&a, &g, &t);
  accMag = sqrt(
    a.acceleration.x * a.acceleration.x +
    a.acceleration.y * a.acceleration.y +
    a.acceleration.z * a.acceleration.z);
}

void readBarometer() {
  if (!baroOk) return;
  relAlt = bmp.readAltitude() - alt0;
  if (state == FLIGHT && relAlt > maxRelAlt) maxRelAlt = relAlt;
}

void updateState() {
  unsigned long now = millis();

  if (state == BOOT) {
    if (now - stateEnterMs >= BOOT_MS) setState(SAFE, "BOOT_DONE");
    return;
  }

  if (state == ARMED && imuOk) {
    if (accMag > LAUNCH_THR) {
      if (launchCondStartMs == 0) launchCondStartMs = now;
      if (now - launchCondStartMs >= LAUNCH_HOLD_MS) {
        setState(FLIGHT, "LAUNCH_IMU");
      }
    } else {
      launchCondStartMs = 0;
    }
  }

  if (state == FLIGHT) {
    if (baroOk && maxRelAlt - relAlt > RECOVERY_DROP_M) {
      setState(RECOVERY, "RECOVERY_ALT");
      return;
    }
    if (now - flightStartMs > RECOVERY_TIMEOUT_MS) {
      setState(RECOVERY, "RECOVERY_TIME");
      return;
    }
  }
}

void updateIndicators() {
  unsigned long now = millis();
  unsigned long period = 1000;
  bool solid = false;

  if (state == BOOT) period = 200;
  if (state == SAFE) period = 1000;
  if (state == ARMED) period = 400;
  if (state == FLIGHT) period = 150;
  if (state == RECOVERY) solid = true;

  if (solid) {
    digitalWrite(LED_PIN, HIGH);
    return;
  }

  if (now - lastBlinkMs >= period) {
    lastBlinkMs = now;
    ledOn = !ledOn;
    digitalWrite(LED_PIN, ledOn ? HIGH : LOW);
  }
}

void printDebug() {
  unsigned long now = millis();
  if (now - lastDebugMs < 100) return;
  lastDebugMs = now;
  Serial.print("[DBG] t=");
  Serial.print(now);
  Serial.print(" st=");
  Serial.print(stateToStr(state));
  Serial.print(" acc=");
  Serial.print(accMag, 2);
  Serial.print(" relAlt=");
  Serial.println(relAlt, 2);
}

void setup() {
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(BUZZER_PIN, OUTPUT);
  Serial.begin(115200);

  Wire.begin();
  imuOk = mpu.begin();
  baroOk = bmp.begin();

  if (baroOk) {
    float sum = 0;
    for (int i = 0; i < 20; i++) {
      sum += bmp.readAltitude();
      delay(30);
    }
    alt0 = sum / 20.0;
  }

  stateEnterMs = millis();
}

void loop() {
  updateButton();
  readIMU();
  readBarometer();
  updateState();
  updateIndicators();
  printDebug();
}
