// 상태 이름 목록
enum State { SAFE, ARMED };

const int BUTTON_PIN = 4;
const int BUZZER_PIN = 9;
const int LED_PIN = 8;

State state = SAFE;

unsigned long pressStartMs = 0;
bool holdConsumed = false;

const unsigned long HOLD_MS = 3000;

void beepOnce(int ms) {
  tone(BUZZER_PIN, 2000, ms);
  delay(ms + 40);
}

void setup() {
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(LED_PIN, OUTPUT);
}

void loop() {
  int reading = digitalRead(BUTTON_PIN);
  unsigned long now = millis();

  // INPUT_PULLUP에서는 LOW가 눌림입니다.
  if (reading == LOW) {
    if (pressStartMs == 0) {
      pressStartMs = now;
    }

    if (!holdConsumed && (now - pressStartMs >= HOLD_MS)) {
      state = (state == SAFE) ? ARMED : SAFE;
      beepOnce(100);
      holdConsumed = true;
    }
  } else {
    pressStartMs = 0;
    holdConsumed = false;
  }

  // 상태 표시: ARMED일 때만 LED ON
  digitalWrite(LED_PIN, state == ARMED ? HIGH : LOW);
}
