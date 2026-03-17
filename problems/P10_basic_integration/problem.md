# P10 - 기본 기능 통합 (SD 제외)

## 문제 설명
지금까지 만든 기능을 하나의 코드로 통합하되, 이번 문제에서는 SD 로깅을 제외한 코어 기능만 완성하세요.

## 요구사항
- 상태는 `BOOT`, `SAFE`, `ARMED`, `FLIGHT`, `RECOVERY`를 사용합니다.
- BOOT 표시 후 SAFE로 자동 전이해야 합니다.
- 버튼 롱프레스로 SAFE/ARMED를 전환해야 합니다.
- IMU 조건으로 ARMED -> FLIGHT 전이를 구현해야 합니다.
- 고도 또는 시간 조건으로 FLIGHT -> RECOVERY 전이를 구현해야 합니다.
- 시리얼 디버그 출력은 포함하고, SD 로깅은 다음 문제에서 추가합니다.
- `delay()` 대신 `millis()`를 사용해야 합니다.

## 구현 방향
template.ino의 함수 TODO를 위에서 아래 순서로 채웁니다.
1. 함수 틀을 먼저 만듭니다: `updateButton`, `readIMU`, `readBarometer`, `updateState`, `printDebug`.
2. P01~P03 코드를 가져와 BOOT/SAFE/버튼/시리얼을 먼저 동작시킵니다.
3. P04~P06 코드를 가져와 IMU와 ARMED->FLIGHT 전이를 추가합니다.
4. P07~P09 코드를 가져와 BARO와 FLIGHT->RECOVERY 전이를 추가합니다.
5. 마지막에 loop 순서를 고정하고(입력->센서->전이->출력), 한 단계씩 테스트합니다.
