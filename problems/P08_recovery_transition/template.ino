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
  // TODO 2: 10초가 지나면 RECOVERY로 전이
}
