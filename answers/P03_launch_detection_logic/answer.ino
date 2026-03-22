// P03 참고 정답
//
// P02에서 추가된 내용:
// - FLIGHT 상태 추가
// - 가속도 크기(accMag) + 유지시간(HOLD_MS)으로 발사 감지
// - accMag가 임계치를 일정 시간 넘을 때만 ARMED -> FLIGHT 전환
#include <Wire.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>

enum State { BOOT, SAFE, ARMED, FLIGHT };

const int LED_PIN = 8;
const int BUTTON_PIN = 4;
const int BUZZER_PIN = 9;
const float THRESHOLD = 17.5;
const unsigned long HOLD_MS = 150;

State state = BOOT;
Adafruit_MPU6050 mpu;

float ax = 0, ay = 0, az = 0;
float accMag = 0;
unsigned long launchStartMs = 0;
unsigned long stateStartMs = 0;
unsigned long lastBlinkMs = 0;
unsigned long lastImuMs = 0;
unsigned long lastDebugMs = 0;

unsigned long pressStartMs = 0;
unsigned long buzzerOffAtMs = 0;
bool beepArmed = false;
bool ledOn = false;

const char* stateToStr(State s) {
  if (s == BOOT) return "BOOT";
  if (s == SAFE) return "SAFE";
  if (s == ARMED) return "ARMED";
  return "FLIGHT";
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
  // 상태 시각은 항상 갱신하고, 실제 전환일 때만 비프/로그를 남깁니다.
  bool changed = (state != next);
  state = next;
  stateStartMs = millis();

  if (!changed) return;
  startBeep(100);

  Serial.print("[STATE] -> ");
  Serial.print(stateToStr(next));
  Serial.print(" reason=");
  Serial.println(reason);
}

void updateButton(unsigned long now) {
  // SAFE/ARMED 롱프레스 전환: 누르고 있으면 3초마다 반복 전환합니다.
  // 수동 전환 시 발사 유지 타이머를 초기화합니다.
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
  // IMU를 50ms 주기로 읽습니다.
  if (now - lastImuMs < 50) return;
  lastImuMs = now;

  sensors_event_t a, g, t;
  mpu.getEvent(&a, &g, &t);
  ax = a.acceleration.x;
  ay = a.acceleration.y;
  az = a.acceleration.z;
  accMag = sqrt(ax * ax + ay * ay + az * az);
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
  digitalWrite(LED_PIN, state == SAFE ? LOW : HIGH);
}

void printDebug(unsigned long now) {
  // 100ms 주기로 디버그를 출력하고 event(임계치 초과 여부)를 포함합니다.
  if (now - lastDebugMs < 100) return;
  lastDebugMs = now;

  bool event = accMag > THRESHOLD;
  Serial.print("[DBG] t=");
  Serial.print(now);
  Serial.print(" state=");
  Serial.print(stateToStr(state));
  Serial.print(" mag=");
  Serial.print(accMag, 2);
  Serial.print(" event=");
  Serial.println(event ? 1 : 0);
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

  setState(BOOT, "INIT");
}

void loop() {
  unsigned long now = millis();
  updateBuzzer(now);

  if (state == BOOT && now - stateStartMs >= 3000) {
    setState(SAFE, "BOOT_DONE");
  }

  if (state != BOOT && state != FLIGHT) {
    updateButton(now);
  }

  updateImu(now);

  // 발사 판정 로직: 임계치 초과가 HOLD_MS 동안 유지되어야 전환합니다.
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

  updateIndicators(now);
  printDebug(now);
}
