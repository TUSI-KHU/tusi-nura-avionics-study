// 상태를 숫자 대신 이름으로 다루기 위한 선언입니다.
enum State { BOOT, SAFE };

const int LED_PIN = 8;
State state = BOOT;

unsigned long stateEnterMs = 0;
unsigned long lastBlinkMs = 0;

// ledOn 변수는 현 LED의 상태를 저장합니다.
// LED가 켜져있으면 true, 꺼져있으면 false입니다.
bool ledOn = false;

void setState(State next) {
  // 함수 매개변수 next는 "다음 상태"를 의미합니다.
  state = next;
  stateEnterMs = millis();
}

void setup() {
  pinMode(LED_PIN, OUTPUT);
  setState(BOOT);
}

void loop() {
  // 현제 시간을 받아옵니다
  unsigned long now = millis();

  // if (조건) { ... } : 조건이 참일 때만 실행됩니다.
  if (state == BOOT) {
    // BOOT 상태입니다.
    //   만약 현제 시간과 마지막으로 LED 상태를 변경한 시간의 차이가 200ms 이상이라면
    // = 마지막으로 LED 상태를 변경한 후 200ms가 지났다면
    if (now - lastBlinkMs >= 200) {
      // 이제 LED 상태를 변경해야 하니 lastBlinkMs를 현제 시간으로 설정합니다
      lastBlinkMs = now;
      // ! 는 NOT 연산자. true<->false 변경
      ledOn = !ledOn;
      // 삼항 연산자입니다. 조건이 참일때는 앞, 조건이 거짓일때는 뒤의 값을 반환합니다.
      // 조건 ? 참 : 거짓
      digitalWrite(LED_PIN, ledOn ? HIGH : LOW);
    }

    // BOOT 상태이며 state가 바뀐 후 3000ms가 지났다면
    // SAFE 스테이트로 바꿉니다.
    if (now - stateEnterMs >= 3000) {
      setState(SAFE);
    }
  } else if (state == SAFE) {
    // SAFE인 경우 LED를 켜면 되니 HIGH로 설정해줍니다.
    digitalWrite(LED_PIN, HIGH);
  }
}
