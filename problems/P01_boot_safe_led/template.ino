// 상태 이름 모음입니다.
// 내부에서는 BOOT=0, SAFE=1 같은 숫자로 저장됩니다.
enum State { BOOT, SAFE };

// 전역변수를 정의합니다.
const int LED_PIN = 8;
State state = BOOT;

unsigned long stateEnterMs = 0;
unsigned long lastBlinkMs = 0;
bool ledOn = false;

// State를 설정하는 함수입니다.
// 전역변수 State state에 새로운 값을 부여합니다.
// 부여 후 시간을 기록합니다.
void setState(State next) {
  state = next;
  stateEnterMs = millis();
}

void setup() {
  pinMode(LED_PIN, OUTPUT);
  setState(BOOT);
}

void loop() {
  // millis() 함수의 반환값에 맞춰 unsigned long을 사용합니다
  // millis() 함수는 아두이노 부팅 이후 지금까지의 시간을 ms로 반환합니다.
  unsigned long now = millis();

  // TODO 1: BOOT 상태
  // STEP 1) 먼저 state가 BOOT일 때만 동작하도록 분기하세요.
  // STEP 2) 점멸 타이머를 비교해서 200ms마다 LED 상태를 반전하세요.
  // STEP 3) BOOT 진입 후 3초가 지났는지 확인해서 SAFE로 전환하세요.
  // - now - lastBlinkMs >= 200 이면 LED 토글
  // - now - stateEnterMs >= 3000 이면 SAFE로 전이

  // TODO 2: SAFE 상태
  // STEP 4) SAFE에서는 조건 없이 LED를 항상 켠 상태로 유지하세요.
  // - LED를 HIGH로 유지
}
