enum State { SAFE, ARMED };

const int BUTTON_PIN = 4;
State state = SAFE;
int lastBtn = HIGH;

unsigned long lastPrintMs = 0;

const char* stateToStr(State s) {
  // return "문자열" 형태로 상태 이름을 돌려줍니다.
  if (s == SAFE) return "SAFE";
  if (s == ARMED) return "ARMED";
  return "UNKNOWN";
}

void setup() {
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  Serial.begin(115200);
}

void loop() {
  // 버튼 입력값을 읽습니다. INPUT_PULLUP 기준으로 눌림은 LOW입니다.
  int btn = digitalRead(BUTTON_PIN);

  if (lastBtn == HIGH && btn == LOW) {
    state = (state == SAFE) ? ARMED : SAFE;
  }
  lastBtn = btn;

  unsigned long now = millis();

  if (now - lastPrintMs >= 100) {
    // 주기 출력 패턴: 현재시간 - 이전출력시간 >= 주기
    lastPrintMs = now;
    Serial.print("[DBG] t=");
    Serial.print(now);
    Serial.print(" state=");
    Serial.print(stateToStr(state));
    Serial.print(" btn=");
    Serial.println(btn);
  }
}
