enum State { BOOT, SAFE, ARMED };

const int LED_PIN = 8;
const int BUTTON_PIN = 4;
const int BUZZER_PIN = 9;

State state = BOOT;
unsigned long stateStartMs = 0;
unsigned long lastBlinkMs = 0;
bool ledOn = false;

unsigned long pressStartMs = 0;

unsigned long buzzerOffAtMs = 0;
bool beepArmed = false;

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

void setState(State next) {
  bool changed = (state != next);
  state = next;
  stateStartMs = millis();

  if (changed) {
    startBeep(100);
  }
}

void setup() {
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(BUZZER_PIN, OUTPUT);
  setState(BOOT);
}

void loop() {
  unsigned long now = millis();
  updateBuzzer(now);

  // TODO 1: BOOT 동작
  // - 200ms 간격으로 LED 점멸
  // - 3초 지나면 SAFE로 바꾸기

  // TODO 2: 버튼 길게 누르기 동작
  // - 3초 누르면 SAFE<->ARMED 전환
  // - 계속 누르고 있으면 3초마다 다시 전환
  // - 버튼을 떼면 pressStartMs 초기화

  // TODO 3: 상태별 표시
  // - ARMED: LED HIGH
  // - SAFE: LED LOW
}
