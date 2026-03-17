#include <Wire.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP085.h>

enum State { BOOT, SAFE, ARMED, FLIGHT, RECOVERY };

const int LED_PIN = 8;
const int BUTTON_PIN = 4;
const int BUZZER_PIN = 9;

State state = BOOT;
unsigned long stateEnterMs = 0;

Adafruit_MPU6050 mpu;
Adafruit_BMP085 bmp;

bool imuOk = false;
bool baroOk = false;

float accMag = 0;
float relAlt = 0;
float alt0 = 0;
float maxRelAlt = 0;

// 함수 선언부입니다.
// loop()에서는 아래 함수들을 순서대로 호출합니다.
void setState(State next, const char* reason);
void updateButton();
void readIMU();
void readBarometer();
void updateState();
void updateIndicators();
void printDebug();

void setup() {
  // TODO 1: 핀 모드, Serial, Wire, 센서 초기화
  // TODO 1-1) 입출력 핀 모드를 먼저 설정하세요.
  // TODO 1-2) 시리얼과 I2C를 시작하세요.
  // TODO 1-3) IMU/BARO 초기화 결과를 imuOk/baroOk에 저장하세요.
  // TODO 1-4) BARO가 정상일 때 기준고도 alt0를 평균으로 계산하세요.
  // TODO 1-5) 초기 상태 진입 시각을 기록하세요.
  // - 버튼은 INPUT_PULLUP, LED/버저는 OUTPUT
  // - bmp 기준고도 alt0 계산 포함
}

void loop() {
  updateButton();
  readIMU();
  readBarometer();
  updateState();
  updateIndicators();
  printDebug();
}

void setState(State next, const char* reason) {
  // TODO 2: 상태 변경 공통 함수
  // TODO 2-1) 상태 변수와 진입 시각을 동시에 갱신하세요.
  // TODO 2-2) 전이 이유를 포함한 상태 로그를 출력하세요.
  // TODO 2-3) FLIGHT 진입 시 flight 시작 시각과 최고고도 추적값을 초기화하세요.
  // - state 변경
  // - stateEnterMs 갱신
  // - 상태 변경 로그 출력
}

void updateButton() {
  // TODO 3: 버튼 처리
  // TODO 3-1) 버튼은 엣지 감지 또는 롱프레스 중 하나의 방식으로 일관되게 처리하세요.
  // TODO 3-2) 상태 전환은 SAFE와 ARMED 사이에서만 일어나게 제한하세요.
  // TODO 3-3) 버튼 보조 변수(이전값/시작시간/잠금 플래그)를 갱신하세요.
  // - 3초 이상 눌리면 SAFE/ARMED 전환
}

void readIMU() {
  // TODO 4: IMU 읽기
  // TODO 4-1) imuOk가 false면 즉시 return 하세요.
  // TODO 4-2) 이벤트를 읽고 3축 가속도 크기 accMag를 계산하세요.
  // - ax, ay, az를 읽어서 accMag 계산
}

void readBarometer() {
  // TODO 5: BARO 읽기
  // TODO 5-1) baroOk가 false면 즉시 return 하세요.
  // TODO 5-2) 현재 상대고도 relAlt를 계산하세요.
  // TODO 5-3) FLIGHT 상태에서는 maxRelAlt를 계속 갱신하세요.
  // - 현재 고도와 alt0로 relAlt 계산
  // - FLIGHT 중 maxRelAlt 갱신
}

void updateState() {
  // TODO 6: 상태 전이 조건 처리
  // TODO 6-1) BOOT 상태에서는 시간 경과로 SAFE 전이를 처리하세요.
  // TODO 6-2) ARMED 상태에서는 IMU 임계치 + 유지시간으로 FLIGHT 전이를 처리하세요.
  // TODO 6-3) FLIGHT 상태에서는 고도 하강 또는 시간 초과로 RECOVERY 전이를 처리하세요.
  // TODO 6-4) 중복 전이를 막기 위해 한 번 전이한 뒤 return 흐름을 점검하세요.
  // - BOOT -> SAFE
  // - ARMED -> FLIGHT
  // - FLIGHT -> RECOVERY
}

void updateIndicators() {
  // TODO 7: 상태 표시
  // TODO 7-1) 상태별 LED 패턴(점멸 주기/고정)을 먼저 정의하세요.
  // TODO 7-2) 점멸은 lastBlinkMs와 ledOn을 이용해 구현하세요.
  // TODO 7-3) 필요하면 전이 이벤트에서만 버저를 울리세요.
  // - 상태에 맞게 LED/버저 처리
}

void printDebug() {
  // TODO 8: 디버그 출력
  // TODO 8-1) 100ms 주기 출력 제한을 먼저 적용하세요.
  // TODO 8-2) 상태, accMag, relAlt를 같은 포맷으로 한 줄 출력하세요.
  // TODO 8-3) 상태 문자열 변환 함수(stateToStr)를 사용하면 읽기 쉽습니다.
  // - 100ms 주기로 state, accMag, relAlt 출력
}
