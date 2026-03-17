# P12 - SD 로그 저장 연습

## 문제 설명
상태와 간단한 센서값(mock 가능)을 CSV로 저장하세요.

## 요구사항
- `flight.csv` 파일에 헤더를 1회 작성합니다.
- 100ms 주기로 한 줄씩 append 합니다.
- 컬럼: `millis,state,accMag,relAlt`
- `delay()` 대신 `millis()`를 사용해야 합니다.

## 구현 방향
template.ino의 `TODO 1 -> TODO 2 -> TODO 3` 순서로 진행합니다.
1. `logEnabled`, `lastLogMs` 변수를 선언합니다.
2. setup에서 SD 초기화 후 `flight.csv` 헤더를 1회 기록합니다.
3. loop에서 `millis() - lastLogMs >= 100`일 때만 기록합니다.
4. 한 줄 기록 형식을 `t,state,accMag,relAlt` 순서로 고정합니다.
5. SD 실패 시 `logEnabled=false`로 두고 나머지 루프는 계속 동작시킵니다.
