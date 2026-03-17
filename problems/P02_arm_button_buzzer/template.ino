// 상태를 이름으로 관리하면 코드 가독성이 좋아집니다.
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

  // TODO 1: 버튼이 눌리면 pressStartMs 기록
  // TODO 2: 3초 이상 눌리고 holdConsumed=false면 상태 변경 + beepOnce(100) + holdConsumed=true
  // TODO 3: 버튼을 떼면 pressStartMs=0, holdConsumed=false로 초기화

  // TODO 4: 상태 표시 LED
  // ARMED면 HIGH, SAFE면 LOW
}
