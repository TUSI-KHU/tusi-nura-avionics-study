# P04 - 기준고도 + 시간 기반 RECOVERY

## 문제 설명
P03에 고도 개념을 추가합니다. 상대고도(`relAlt`)를 만들고, `FLIGHT -> RECOVERY`를 시간 조건으로 먼저 구현합니다.

## 요구사항
- 상태에 `RECOVERY`를 추가합니다.
- BMP180 초기화 후 기준고도 `alt0`를 평균으로 계산합니다.
- `relAlt = alt - alt0`를 100ms 디버그에 출력합니다.
- `FLIGHT`에 들어간 뒤 10초가 지나면 `RECOVERY`로 바꿉니다.
- 상태가 바뀐 이유(reason)는 `TIME`으로 출력합니다.

## 구현 방향
template.ino의 `TODO 1 -> TODO 4` 순서로 진행하세요.
1. BMP180 초기화와 `alt0` 계산을 추가합니다.
2. 주기적으로 `relAlt`를 업데이트합니다.
3. FLIGHT 시작 시간을 저장합니다.
4. 10초 조건으로 RECOVERY 상태 변경을 구현합니다.
