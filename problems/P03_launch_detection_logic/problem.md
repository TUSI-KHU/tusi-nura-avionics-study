# P03 - IMU 이벤트 감지 + FLIGHT 상태 변경

## 문제 설명
P02를 확장해 `ARMED -> FLIGHT` 상태 변경을 구현합니다. 값이 잠깐 넘는 경우가 아니라, 일정 시간 유지될 때만 바꾸는 것이 핵심입니다.

## 요구사항
- 상태에 `FLIGHT`를 추가합니다.
- `mag = sqrt(ax*ax + ay*ay + az*az)`를 계산합니다.
- `mag > THRESHOLD`가 `HOLD_MS` 동안 계속 유지되면 `FLIGHT`로 바꿉니다.
- 권장값: `THRESHOLD=17.5`, `HOLD_MS=150`.
- 디버그에 `mag`, `event`를 포함합니다.

## 구현 방향
template.ino의 `TODO 1 -> TODO 3` 순서로 진행하세요.
1. `accMag`를 계산하고 이벤트 후보(`event`)를 만듭니다.
2. 시간 재는 변수(`launchStartMs`)를 구현합니다.
3. 조건을 만족하면 reason=`IMU_HOLD`로 상태 로그를 남깁니다.
