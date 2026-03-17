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
  // STEP 1) INPUT_PULLUP 기준으로 눌림(LOW)일 때만 눌림 처리 블록에 들어가세요.
  // STEP 2) 처음 눌린 순간 1회만 시작 시간을 저장하세요.
  // TODO 2: 3초 이상 눌리고 holdConsumed=false면 상태 변경 + beepOnce(100) + holdConsumed=true
  // STEP 3) 눌림 시간이 HOLD_MS를 넘고 아직 처리하지 않았으면 상태를 1회만 바꾸세요.
  // STEP 4) 상태 변경 직후 버저를 울리고, 같은 누름에서 재실행되지 않게 잠그세요.
  // TODO 3: 버튼을 떼면 pressStartMs=0, holdConsumed=false로 초기화
  // STEP 5) 버튼을 떼는 순간 시작시간/잠금 플래그를 초기화하세요.

  // TODO 4: 상태 표시 LED
  // STEP 6) 루프 마지막에서 상태에 따라 LED를 켜거나 끄세요.
  // ARMED면 HIGH, SAFE면 LOW
}
