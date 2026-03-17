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
  // TODO 2: IMU 읽고 가속도 크기 mag 계산
  // TODO 3: ARMED에서 mag > THRESHOLD가 HOLD_MS 유지되면 FLIGHT
}
