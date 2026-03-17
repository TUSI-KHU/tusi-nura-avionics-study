enum State { SAFE, ARMED };

const int BUTTON_PIN = 4;
State state = SAFE;
int lastBtn = HIGH;

// 마지막으로 로그를 출력한 시간을 저장합니다.
unsigned long lastPrintMs = 0;

const char* stateToStr(State s) {
  // TODO: 상태 값을 문자열로 바꿔서 반환
  // const char* 는 문자열을 돌려줄 때 자주 쓰는 타입입니다.
  return "UNKNOWN";
}

void setup() {
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  Serial.begin(115200);
}

void loop() {
  // digitalRead는 HIGH(1) 또는 LOW(0)를 반환합니다.
  int btn = digitalRead(BUTTON_PIN);

  // TODO 1: HIGH->LOW 눌리는 순간에 SAFE/ARMED 변경
  // if (lastBtn == HIGH && btn == LOW) { ... }

  // TODO 2: 마지막 버튼값 업데이트
  // lastBtn = btn;

  // TODO 3: 100ms마다 디버그 한 줄 출력
}
