# P01 - BOOT/SAFE 상태등 만들기

## 문제 설명
LED 1개로 FC의 기본 상태를 표현하세요.

## 요구사항
- 상태를 `BOOT`, `SAFE`로 정의합니다
- `BOOT`: 아두이노 부팅 후 3초 동안 200ms 간격으로 LED를 점멸해야 합니다.
- `SAFE`: LED를 계속 켜둡니다.
- `delay()` 대신 `millis()`를 사용해야 합니다.

## 구현 방향
template.ino의 `TODO 1 -> TODO 2` 순서로 진행합니다.
1. `enum State { BOOT, SAFE };`를 선언하고 `state` 전역변수를 만듭니다.
2. `setState()` 함수를 만들어 상태 변경 시 `stateEnterMs = millis()`를 기록합니다.
3. `loop()`에서 `now = millis()`를 읽고, `state == BOOT`일 때 점멸 로직을 작성합니다.
4. `now - stateEnterMs >= 3000` 조건에서 `setState(SAFE)`를 호출합니다.
5. `state == SAFE`에서는 LED를 `HIGH`로 유지합니다.
