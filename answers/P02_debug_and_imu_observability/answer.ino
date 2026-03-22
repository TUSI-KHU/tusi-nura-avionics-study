// P02 참고 정답
//
// P01에서 추가된 내용:
// - IMU를 50ms 주기로 읽기
// - 디버그를 100ms 주기로 출력
// - P01 동작(BOOT/SAFE/ARMED, 롱프레스 전환, LED, 비프음) 유지
#include <Wire.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>

enum State { BOOT, SAFE, ARMED };

const int LED_PIN = 8;
const int BUTTON_PIN = 4;
const int BUZZER_PIN = 9;

State state = BOOT;
Adafruit_MPU6050 mpu;

float ax = 0, ay = 0, az = 0;
unsigned long stateStartMs = 0;
unsigned long lastBlinkMs = 0;
unsigned long lastImuMs = 0;
unsigned long lastDebugMs = 0;

unsigned long pressStartMs = 0;
unsigned long buzzerOffAtMs = 0;
bool beepArmed = false;
bool ledOn = false;

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

const char* stateToStr(State s) {
  if (s == BOOT) return "BOOT";
  if (s == SAFE) return "SAFE";
  return "ARMED";
}

void setState(State next) {
  // 상태 시작 시각은 항상 갱신하고, 실제 상태 변경일 때만 비프음을 냅니다.
  bool changed = (state != next);
  state = next;
  stateStartMs = millis();
  if (changed) {
    startBeep(100);
  }
}

void updateButton(unsigned long now) {
  // 롱프레스를 유지하면 3초 구간마다 1회씩 반복 전환합니다.
  int btn = digitalRead(BUTTON_PIN);
  if (btn == LOW) {
    if (pressStartMs == 0) pressStartMs = now;
    if (now - pressStartMs >= 3000) {
      setState(state == SAFE ? ARMED : SAFE);
      pressStartMs = now;
    }
  } else {
    pressStartMs = 0;
  }
}

void updateImu(unsigned long now) {
  // IMU 작업을 50ms 주기로 실행합니다.
  if (now - lastImuMs < 50) return;
  lastImuMs = now;

  sensors_event_t a, g, t;
  mpu.getEvent(&a, &g, &t);
  ax = a.acceleration.x;
  ay = a.acceleration.y;
  az = a.acceleration.z;
}

void updateIndicators(unsigned long now) {
  // BOOT는 점멸, ARMED는 고정 ON, SAFE는 고정 OFF입니다.
  if (state == BOOT) {
    if (now - lastBlinkMs >= 200) {
      lastBlinkMs = now;
      ledOn = !ledOn;
      digitalWrite(LED_PIN, ledOn ? HIGH : LOW);
    }
    return;
  }
  digitalWrite(LED_PIN, state == ARMED ? HIGH : LOW);
}

void printDebug(unsigned long now) {
  // 디버그 출력 작업을 100ms 주기로 실행합니다.
  if (now - lastDebugMs < 100) return;
  lastDebugMs = now;

  Serial.print("[DBG] t=");
  Serial.print(now);
  Serial.print(" state=");
  Serial.print(stateToStr(state));
  Serial.print(" btn=");
  Serial.print(digitalRead(BUTTON_PIN));
  Serial.print(" ax=");
  Serial.print(ax, 2);
  Serial.print(" ay=");
  Serial.print(ay, 2);
  Serial.print(" az=");
  Serial.println(az, 2);
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

  setState(BOOT);
}

void loop() {
  unsigned long now = millis();
  updateBuzzer(now);

  if (state == BOOT && now - stateStartMs >= 3000) {
    setState(SAFE);
  }

  if (state != BOOT) {
    updateButton(now);
  }

  updateImu(now);
  updateIndicators(now);
  printDebug(now);
}
