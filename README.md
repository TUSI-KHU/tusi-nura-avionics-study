# 2주 미니 Flight Computer 학습 자료

이 저장소는 아두이노 입문자를 위한 단계형 실습 자료입니다.

핵심 설계 원칙:
- 각 문제는 **독립 실행 가능한 미니 프로젝트**입니다.
- 학생이 반드시 하나의 거대한 코드베이스를 계속 이어서 쓰지 않아도 됩니다.
- 각 문제 폴더는 아래 3개 파일로 구성됩니다.
  - `problem.md`: 코딩테스트형 문제지
  - `template.ino`: 시작 코드(빈칸/TODO 포함)
  - `answer.ino`: 정답 예시 코드(초보자용 설명 주석 포함)

## 폴더 구성

- `docs/learner_guide.md`: 학습자용 가이드(학습 순서 + 기초 설명)
- `problems/P01_boot_safe_led/`
- `problems/P02_arm_button_buzzer/`
- `problems/P03_serial_debug/`
- `problems/P04_read_mpu6050/`
- `problems/P05_imu_magnitude_threshold/`
- `problems/P06_launch_detection_flight_transition/`
- `problems/P07_read_bmp180_altitude/`
- `problems/P08_recovery_transition/`
- `problems/P09_recovery_altitude/`
- `problems/P10_basic_integration/`
- `problems/P11_sd_basic_check/`
- `problems/P12_sd_flight_logging/`
- `problems/P13_integration_with_sd/`
- `problems/P14_full_system_check/`

## 권장 학습 방식

1. `problem.md`를 먼저 읽고 목표를 확인합니다.
2. `template.ino`의 TODO를 순서대로 채웁니다.
3. 업로드 후 시리얼 모니터로 동작을 확인합니다.
4. 막히면 `answer.ino`와 비교해서 차이를 찾습니다.
5. 마지막(P14)에서 전체 기능을 점검합니다.

## 단계별 학습 경로 (총 14문제)

각 폴더는 분리되어 있지만, 학습 흐름은 아래처럼 "천천히 진화"하도록 설계되어 있습니다.

1. `P01`: BOOT/SAFE LED 상태 표현
2. `P02`: 버튼 입력과 버저 피드백 추가
3. `P03`: 상태/입력 시리얼 관측 추가
4. `P04`: IMU 센서 입력 채널 추가
5. `P05`: IMU 크기값과 이벤트 후보 판정 추가
6. `P06`: 가속도 조건으로 ARMED -> FLIGHT 전이
7. `P07`: BARO 상대고도 채널 추가
8. `P08`: 시간 조건 RECOVERY 전이
9. `P09`: 고도 조건 RECOVERY 전이
10. `P10`: 기본 기능 통합 (상태/센서/전이, SD 제외)
11. `P11`: SD 기본 동작 확인
12. `P12`: SD 로그 저장 연습
13. `P13`: 기본 기능 + SD 통합
14. `P14`: 전체 동작 점검

즉, 폴더는 독립 제출용이지만 내용은 FC 목표로 이어지는 순차 구조입니다.
