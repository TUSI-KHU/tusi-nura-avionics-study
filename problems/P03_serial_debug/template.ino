enum State { SAFE, ARMED };

const int BUTTON_PIN = 4;
State state = SAFE;
int lastBtn = HIGH;

// 마지막으로 로그를 출력한 시간을 저장합니다.
unsigned long lastPrintMs = 0;

const char* stateToStr(State s) {
  // TODO: 상태 값을 문자열로 바꿔서 반환
  // STEP 1) 각 상태값을 사람이 읽는 문자열로 반환하세요.
  // STEP 2) 정의되지 않은 값은 UNKNOWN으로 반환하세요.
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
  // STEP 3) 이전값과 현재값을 비교해서 "눌린 순간"(HIGH->LOW)만 감지하세요.
  // STEP 4) 그 순간에만 SAFE/ARMED를 토글하세요.
  // if (lastBtn == HIGH && btn == LOW) { ... }

  // TODO 2: 마지막 버튼값 업데이트
  // STEP 5) 루프 끝으로 가기 전에 현재 버튼값을 lastBtn에 저장하세요.
  // lastBtn = btn;

  // TODO 3: 100ms마다 디버그 한 줄 출력
  // STEP 6) millis()로 현재 시간을 읽고 100ms 간격 조건을 만드세요.
  // STEP 7) 시간, 상태 문자열, 버튼값을 같은 포맷으로 한 줄 출력하세요.
}
