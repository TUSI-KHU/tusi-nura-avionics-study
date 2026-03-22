// P05 참고 정답
//
// 목표:
// - BOOT -> SAFE -> ARMED -> FLIGHT -> RECOVERY를 한 코드로 통합
// - loop 순서를 입력 -> 센서 -> 상태 업데이트 -> 출력으로 고정
// - 이 단계에서는 RECOVERY를 시간 조건으로 처리
#include <Wire.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP085.h>

enum State { BOOT, SAFE, ARMED, FLIGHT, RECOVERY };

const int LED_PIN = 8;
const int BUTTON_PIN = 4;
const int BUZZER_PIN = 9;
const float LAUNCH_THR = 17.5;
const unsigned long LAUNCH_HOLD_MS = 150;
const unsigned long RECOVERY_TIMEOUT_MS = 10000;

Adafruit_MPU6050 mpu;
Adafruit_BMP085 bmp;

State state = BOOT;
unsigned long stateStartMs = 0;
unsigned long flightStartMs = 0;
unsigned long launchStartMs = 0;
unsigned long lastImuMs = 0;
unsigned long lastBaroMs = 0;
unsigned long lastDebugMs = 0;
unsigned long lastBlinkMs = 0;

unsigned long pressStartMs = 0;

float accMag = 0;
float relAlt = 0;
float alt0 = 0;

bool ledOn = false;
unsigned long buzzerOffAtMs = 0;
bool beepArmed = false;

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
  // 공통 상태 전환 함수입니다.
  // 상태 시각은 항상 갱신하고, FLIGHT 진입 시 flightStartMs를 저장합니다.
  // 실제 상태 전환일 때만 비프/로그를 실행합니다.
  bool changed = (state != next);

  state = next;
  stateStartMs = millis();

  if (next == FLIGHT) {
    flightStartMs = stateStartMs;
  }

  if (!changed) return;
  startBeep(100);

  Serial.print("[STATE] ");
  Serial.print(stateToStr(next));
  Serial.print(" reason=");
  Serial.println(reason);
}

void updateInput(unsigned long now) {
  // 사용자 입력은 SAFE/ARMED에서만 처리합니다.
  if (state != SAFE && state != ARMED) return;

  int btn = digitalRead(BUTTON_PIN);
  if (btn == LOW) {
    if (pressStartMs == 0) pressStartMs = now;
    if (now - pressStartMs >= 3000) {
      if (state == SAFE) setState(ARMED, "BUTTON");
      else setState(SAFE, "BUTTON");
      pressStartMs = now;
      launchStartMs = 0;
    }
  } else {
    pressStartMs = 0;
  }
}

void updateSensors(unsigned long now) {
  // IMU(50ms): 가속도 크기 accMag 갱신
  if (now - lastImuMs >= 50) {
    lastImuMs = now;
    sensors_event_t a, g, t;
    mpu.getEvent(&a, &g, &t);
    accMag = sqrt(
      a.acceleration.x * a.acceleration.x +
      a.acceleration.y * a.acceleration.y +
      a.acceleration.z * a.acceleration.z);
  }

  // BARO(100ms): 상대고도 relAlt 갱신
  if (now - lastBaroMs >= 100) {
    lastBaroMs = now;
    relAlt = bmp.readAltitude() - alt0;
  }
}

void updateState(unsigned long now) {
  // BOOT는 3초 후 자동으로 SAFE로 전환합니다.
  if (state == BOOT) {
    if (now - stateStartMs >= 3000) setState(SAFE, "BOOT_DONE");
    return;
  }

  // ARMED 발사 판정: 임계치 초과가 일정 시간 유지되어야 합니다.
  if (state == ARMED) {
    if (accMag > LAUNCH_THR) {
      if (launchStartMs == 0) launchStartMs = now;
      if (now - launchStartMs >= LAUNCH_HOLD_MS) {
        setState(FLIGHT, "IMU_HOLD");
        launchStartMs = 0;
      }
    } else {
      launchStartMs = 0;
    }
    return;
  }

  // P05 RECOVERY는 시간 조건만 사용합니다.
  if (state == FLIGHT) {
    if (now - flightStartMs >= RECOVERY_TIMEOUT_MS) {
      setState(RECOVERY, "TIME");
      return;
    }
  }
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
  Serial.print(" accMag=");
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
  updateInput(now);
  updateSensors(now);
  updateState(now);
  updateIndicators(now);
  printDebug(now);
}
