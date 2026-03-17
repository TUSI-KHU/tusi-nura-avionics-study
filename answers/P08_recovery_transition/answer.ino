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
  if (state == FLIGHT) {
    if (millis() - flightStartMs > 10000) {
      setState(RECOVERY, "TIME");
    }
  }
}
