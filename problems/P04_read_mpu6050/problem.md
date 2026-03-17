# P04 - MPU6050 값 읽기

## 문제 설명
MPU6050 센서를 초기화하고 가속도 값을 주기적으로 출력하세요.

## 요구사항
- Nano I2C 핀(`A4=SDA`, `A5=SCL`)으로 연결합니다.
- 센서 초기화 실패 시 에러 로그를 출력하고 중지합니다.
- 50ms 간격으로 `ax`, `ay`, `az`를 출력합니다.

## 구현 방향
template.ino의 `TODO 1 -> TODO 2 -> TODO 3` 순서로 진행합니다.
1. `Wire.begin()` 호출 후 `mpu.begin()`으로 센서를 초기화합니다.
2. 초기화 실패 시 `[ERR]`를 출력하고 `while (1)`로 정지합니다.
3. `sensors_event_t a, g, t;`를 선언하고 `mpu.getEvent(&a, &g, &t)`로 값을 읽습니다.
4. `lastPrintMs`를 사용해 50ms마다만 출력합니다.
5. 출력값은 `a.acceleration.x`, `y`, `z`를 그대로 사용합니다.
