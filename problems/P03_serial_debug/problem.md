# P03 - 시리얼 디버그 출력 만들기

## 문제 설명
현재 상태를 사람이 읽기 쉽게 시리얼로 주기 출력하세요.

## 요구사항
- 100ms 간격으로 로그를 출력합니다.
- 로그에는 `millis`, 상태 문자열, 버튼 값을 포함합니다.
- 출력 형식은 예시처럼 통일합니다: `[DBG] t=1234 state=SAFE btn=1`
- `delay()` 대신 `millis()`를 사용해야 합니다.

## 구현 방향
template.ino의 `stateToStr TODO -> TODO 1 -> TODO 2 -> TODO 3` 순서로 진행합니다.
1. `stateToStr(State s)` 함수를 만들어 상태(enum)를 문자열로 변환합니다.
2. `lastPrintMs` 전역변수를 선언하고 마지막 출력 시각을 저장합니다.
3. `loop()`에서 버튼 입력을 읽고(필요하면 상태 토글도 같이 처리), `now = millis()`를 구합니다.
4. `if (now - lastPrintMs >= 100)`에서만 출력하도록 제한합니다.
5. 출력 키(`t`, `state`, `btn`) 순서를 고정해 이후 문제에서도 같은 형식을 유지합니다.
