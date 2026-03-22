// P04 참고 정답
//
// P03에서 추가된 내용:
// - BMP180 기준고도 보정(alt0)
// - 상대고도 relAlt = 현재 고도 - alt0
// - FLIGHT -> RECOVERY를 시간 조건(10초)으로 전환
#include <Wire.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP085.h>

enum State { BOOT, SAFE, ARMED, FLIGHT, RECOVERY };

const int LED_PIN = 8;
const int BUTTON_PIN = 4;
const int BUZZER_PIN = 9;
const float THRESHOLD = 17.5;
const unsigned long HOLD_MS = 150;
const unsigned long RECOVERY_TIME_MS = 10000;

Adafruit_MPU6050 mpu;
Adafruit_BMP085 bmp;

State state = BOOT;
float ax = 0, ay = 0, az = 0;
float accMag = 0;
float alt0 = 0;
float relAlt = 0;

unsigned long stateStartMs = 0;
unsigned long flightStartMs = 0;
unsigned long launchStartMs = 0;
unsigned long lastBlinkMs = 0;
unsigned long lastImuMs = 0;
unsigned long lastBaroMs = 0;
unsigned long lastDebugMs = 0;

unsigned long pressStartMs = 0;
unsigned long buzzerOffAtMs = 0;
bool beepArmed = false;
bool ledOn = false;

const char* stateToStr(State s) {
  if (s == BOOT) return "BOOT";
  if (s == SAFE) return "SAFE";
  if (s == ARMED) return "ARMED";
  if (s == FLIGHT) return "FLIGHT";
  return "RECOVERY";
}

void startBeep(unsigned long ms) {
  tone(BUZZER_PIN, 2000);
  buzzerOffAtMs = millis() + ms;
  beepArmed = true;
}

void updateBuzzer(unsigned long now) {
  if (beepArmed && now >= buzzerOffAtMs) {
    noTone(BUZZER_PIN);
    beepArmed = false;
  }
}

void setState(State next, const char* reason) {
  // 상태 시각은 항상 갱신하고, FLIGHT 진입 시 비행 시작 시각을 저장합니다.
  // 실제 전환일 때만 비프/로그를 남깁니다.
  bool changed = (state != next);
  state = next;
  stateStartMs = millis();

  if (next == FLIGHT) {
    flightStartMs = stateStartMs;
  }

  if (!changed) return;
  startBeep(100);

  Serial.print("[STATE] -> ");
  Serial.print(stateToStr(next));
  Serial.print(" reason=");
  Serial.println(reason);
}

void updateButton(unsigned long now) {
  // 버튼 입력은 SAFE/ARMED 전환에만 사용합니다.
  int btn = digitalRead(BUTTON_PIN);
  if (btn == LOW) {
    if (pressStartMs == 0) pressStartMs = now;
    if (now - pressStartMs >= 3000) {
      if (state == SAFE) setState(ARMED, "BUTTON");
      else if (state == ARMED) setState(SAFE, "BUTTON");
      pressStartMs = now;
      launchStartMs = 0;
    }
  } else {
    pressStartMs = 0;
  }
}

void updateImu(unsigned long now) {
  // IMU를 50ms 주기로 읽고 accMag를 계산합니다.
  if (now - lastImuMs < 50) return;
  lastImuMs = now;

  sensors_event_t a, g, t;
  mpu.getEvent(&a, &g, &t);
  ax = a.acceleration.x;
  ay = a.acceleration.y;
  az = a.acceleration.z;
  accMag = sqrt(ax * ax + ay * ay + az * az);
}

void updateBaro(unsigned long now) {
  // 기압계를 100ms 주기로 읽어 상대고도를 계산합니다.
  if (now - lastBaroMs < 100) return;
  lastBaroMs = now;
  relAlt = bmp.readAltitude() - alt0;
}

void updateIndicators(unsigned long now) {
  if (state == BOOT) {
    if (now - lastBlinkMs >= 200) {
      lastBlinkMs = now;
      ledOn = !ledOn;
      digitalWrite(LED_PIN, ledOn ? HIGH : LOW);
    }
    return;
  }

  if (state == SAFE) digitalWrite(LED_PIN, LOW);
  else digitalWrite(LED_PIN, HIGH);
}

void printDebug(unsigned long now) {
  if (now - lastDebugMs < 100) return;
  lastDebugMs = now;

  Serial.print("[DBG] t=");
  Serial.print(now);
  Serial.print(" state=");
  Serial.print(stateToStr(state));
  Serial.print(" mag=");
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
  if (!mpu.begin()) {
    Serial.println("[ERR] MPU6050 init failed");
    while (1) {}
  }
  if (!bmp.begin()) {
    Serial.println("[ERR] BMP180 init failed");
    while (1) {}
  }

  // 시작 시 여러 샘플 평균으로 기준고도 alt0를 구합니다.
  float sum = 0;
  for (int i = 0; i < 20; i++) {
    sum += bmp.readAltitude();
  }
  alt0 = sum / 20.0;

  setState(BOOT, "INIT");
}

void loop() {
  unsigned long now = millis();
  updateBuzzer(now);

  if (state == BOOT && now - stateStartMs >= 3000) {
    setState(SAFE, "BOOT_DONE");
  }

  if (state == SAFE || state == ARMED) {
    updateButton(now);
  }

  updateImu(now);
  updateBaro(now);

  // 발사 판정 로직(P03과 동일한 패턴).
  if (state == ARMED) {
    if (accMag > THRESHOLD) {
      if (launchStartMs == 0) launchStartMs = now;
      if (now - launchStartMs >= HOLD_MS) {
        setState(FLIGHT, "IMU_HOLD");
        launchStartMs = 0;
      }
    } else {
      launchStartMs = 0;
    }
  }

  // P04 RECOVERY 규칙: 시간 조건만 사용합니다.
  if (state == FLIGHT && now - flightStartMs >= RECOVERY_TIME_MS) {
    setState(RECOVERY, "TIME");
  }

  updateIndicators(now);
  printDebug(now);
}
