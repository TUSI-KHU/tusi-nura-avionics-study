#include <Wire.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>

enum State { SAFE, ARMED, FLIGHT };

const int BUTTON_PIN = 4;
State state = SAFE;

int lastBtn = HIGH;

Adafruit_MPU6050 mpu;

const float THRESHOLD = 17.5;
const unsigned long HOLD_MS = 150;
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
  int btn = digitalRead(BUTTON_PIN);
  // 버튼이 눌리는 순간: 이전 HIGH, 현재 LOW
  if (lastBtn == HIGH && btn == LOW) {
    if (state == SAFE) {
      state = ARMED;
      Serial.println("[STATE] SAFE->ARMED");
    } else if (state == ARMED) {
      state = SAFE;
      Serial.println("[STATE] ARMED->SAFE");
    }
  }
  lastBtn = btn;

  sensors_event_t a, g, t;
  mpu.getEvent(&a, &g, &t);

  // 가속도 벡터의 크기 계산
  float mag = sqrt(
    a.acceleration.x * a.acceleration.x +
    a.acceleration.y * a.acceleration.y +
    a.acceleration.z * a.acceleration.z);

  if (state == ARMED) {
    // 임계치 + 지속시간 알고리즘
    if (mag > THRESHOLD) {
      // 조건이 처음 만족될 때 시작 시각을 기록합니다.
      if (launchCondStartMs == 0) launchCondStartMs = millis();
      if (millis() - launchCondStartMs >= HOLD_MS) {
        state = FLIGHT;
        Serial.println("[STATE] ARMED->FLIGHT (launch detected)");
      }
    } else {
      // 조건이 깨지면 타이머를 초기화합니다.
      launchCondStartMs = 0;
    }
  }
}
