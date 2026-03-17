# P06 - 가속도 조건으로 FLIGHT 전이

## 문제 설명
`ARMED` 상태에서 가속도 조건이 만족되면 `FLIGHT`로 전이하는 로직을 구현하세요.

## 요구사항
- 상태를 `SAFE`, `ARMED`, `FLIGHT`로 정의합니다.
- 버튼(`INPUT_PULLUP`)으로 SAFE/ARMED를 전환합니다.
- `ARMED` 상태에서 `mag > THRESHOLD`가 `HOLD_MS` 동안 유지되면 FLIGHT로 전이합니다.
- 권장 기본값은 `THRESHOLD=17.5`, `HOLD_MS=150`입니다.

## 구현 방향
template.ino의 `TODO 1 -> TODO 2 -> TODO 3` 순서로 진행합니다.
1. P02의 버튼 "눌리는 순간" 처리 코드를 가져와 SAFE/ARMED 전환을 먼저 완성합니다.
2. P05의 `mag` 계산 코드를 가져옵니다.
3. `launchCondStartMs` 변수를 두고 조건이 처음 참인 시각을 기록합니다.
4. 조건이 계속 참이면 `now - launchCondStartMs >= HOLD_MS`에서 FLIGHT로 전이합니다.
5. 조건이 거짓이 되면 `launchCondStartMs = 0`으로 초기화합니다.
