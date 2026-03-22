# P05 - 코어 상태머신 통합 (시간 RECOVERY)

## 문제 설명
지금까지 만든 기능을 한 코드로 합칩니다. 이번 단계의 RECOVERY는 시간 조건만 사용해서 복잡도를 낮춥니다.

## 요구사항
- 상태 흐름: `BOOT -> SAFE -> ARMED -> FLIGHT -> RECOVERY`
- `ARMED -> FLIGHT`: IMU 임계치 + 유지 시간
- `FLIGHT -> RECOVERY`: `flightStartMs` 기준 10초 뒤 reason=`TIME`
- 디버그에 `state, accMag, relAlt`를 100ms마다 출력합니다.
- loop 순서는 `입력 -> 센서 -> 상태 변경 -> 출력`으로 고정합니다.

## 구현 방향
template.ino의 함수 TODO를 위에서 아래로 채우세요.
1. P04 코드를 함수 단위로 정리합니다.
2. 상태 변경 코드를 `updateState()` 한 곳에 모읍니다.
3. `setState()`에서 FLIGHT 시작 시간(`flightStartMs`)을 설정합니다.
