// P01 참고 정답
//
// 로직 요약:
// 1) BOOT 상태에서 200ms마다 LED를 깜빡이며 3초 대기합니다.
// 2) 3초가 지나면 SAFE로 상태를 바꿉니다.
// 3) SAFE/ARMED에서 버튼을 3초 누르면 상태를 전환합니다.
//    계속 누르고 있으면 3초마다 다시 전환합니다.
// 4) ARMED에서는 LED ON, SAFE에서는 LED OFF를 유지합니다.
// 5) 상태가 바뀌면 100ms 비프음을 비차단 방식으로 냅니다.
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
  // 지금 비프음을 시작하고, 언제 끌지 시각을 저장합니다.
  tone(BUZZER_PIN, 2000);
  buzzerOffAtMs = millis() + ms;
  beepArmed = true;
}

void updateBuzzer(unsigned long now) {
  // 비차단 방식으로 비프 종료 시각을 확인합니다.
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

  // BOOT: 점멸 후 3초가 지나면 SAFE로 전환합니다.
  if (state == BOOT) {
    if (now - lastBlinkMs >= 200) {
      lastBlinkMs = now;
      ledOn = !ledOn;
      digitalWrite(LED_PIN, ledOn ? HIGH : LOW);
    }
    if (now - stateStartMs >= 3000) {
      setState(SAFE);
      ledOn = false;
    }
    return;
  }

  // 롱프레스 전환 로직:
  // 버튼을 떼면 pressStartMs를 0으로 초기화하고,
  // 전환 후 pressStartMs를 now로 갱신해서 누르고 있는 동안 3초마다 재전환합니다.
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

  digitalWrite(LED_PIN, state == ARMED ? HIGH : LOW);
}
