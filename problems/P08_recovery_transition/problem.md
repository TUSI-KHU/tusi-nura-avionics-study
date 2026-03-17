# P08 - 시간 조건 RECOVERY 전이

## 문제 설명
`FLIGHT` 상태에서 일정 시간이 지나면 `RECOVERY`로 전이하는 가장 쉬운 버전을 구현하세요.

## 요구사항
- 상태를 `FLIGHT`, `RECOVERY`로 정의합니다.
- `FLIGHT` 시작 시간을 `flightStartMs`에 저장합니다.
- `millis() - flightStartMs > 10000`이면 `RECOVERY`로 전이합니다.
- 전이 시 시리얼 로그를 출력합니다.

## 구현 방향
template.ino의 `TODO 1 -> TODO 2` 순서로 진행합니다.
1. 시작 상태를 `FLIGHT`로 두고 `setup()`에서 `flightStartMs = millis()`를 기록합니다.
2. `setState(next, reason)` 함수를 만들어 상태 변경과 로그 출력을 같이 처리합니다.
3. loop에서 `if (state == FLIGHT)` 조건 안에서만 전이 조건을 검사합니다.
4. 10초가 지나면 `setState(RECOVERY, "TIME")`를 호출합니다.
5. RECOVERY 이후에는 전이 검사를 더 하지 않도록 유지합니다.
