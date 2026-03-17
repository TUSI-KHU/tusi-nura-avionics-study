enum State { FLIGHT, RECOVERY };

State state = FLIGHT;
unsigned long flightStartMs = 0;

void setState(State next, const char* reason) {
  state = next;
  Serial.print("[STATE] -> ");
  Serial.print(next == FLIGHT ? "FLIGHT" : "RECOVERY");
  Serial.print(" reason=");
  Serial.println(reason);
}

void setup() {
  Serial.begin(115200);
  flightStartMs = millis();
}

void loop() {
  // TODO 1: FLIGHT 상태인지 확인
  // STEP 1) 먼저 state가 FLIGHT일 때만 검사하도록 분기하세요.
  // TODO 2: 10초가 지나면 RECOVERY로 전이
  // STEP 2) FLIGHT 시작 시간 대비 10초 경과를 검사하세요.
  // STEP 3) 조건이 맞으면 setState를 통해 RECOVERY로 전환하고 reason을 남기세요.
}
