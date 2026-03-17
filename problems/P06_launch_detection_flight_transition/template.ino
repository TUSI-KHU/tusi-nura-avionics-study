#include <Wire.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>

enum State { SAFE, ARMED, FLIGHT };

const int BUTTON_PIN = 4;
State state = SAFE;

Adafruit_MPU6050 mpu;

const float THRESHOLD = 17.5;
const unsigned long HOLD_MS = 150;
// 조건이 처음 참이 된 시각을 저장합니다.
unsigned long launchCondStartMs = 0;
int lastBtn = HIGH;

void setup() {
  Serial.begin(115200);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  Wire.begin();
  if (!mpu.begin()) {
    Serial.println("[ERR] MPU init failed");
    while (1) delay(1000);
  }
}

void loop() {
  // TODO 1: 버튼 눌리는 순간(HIGH->LOW)에서 SAFE/ARMED 변경
  // STEP 1) 버튼 이전값/현재값으로 눌린 순간만 감지하세요.
  // STEP 2) 눌린 순간에 SAFE와 ARMED를 서로 전환하세요.
  // STEP 3) 마지막에 현재 버튼값을 갱신하세요.

  // TODO 2: IMU 읽고 가속도 크기 mag 계산
  // STEP 4) 센서 이벤트를 읽고 3축 값으로 mag를 계산하세요.

  // TODO 3: ARMED에서 mag > THRESHOLD가 HOLD_MS 유지되면 FLIGHT
  // STEP 5) 이 전이 검사는 ARMED 상태에서만 수행하세요.
  // STEP 6) 임계치 초과가 시작된 시점을 기록하고 HOLD_MS 유지 여부를 확인하세요.
  // STEP 7) 중간에 임계치가 깨지면 시작 시점을 초기화하세요.
}
