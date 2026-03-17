# P09 - 고도 조건 RECOVERY 전이

## 문제 설명
P08의 시간 기반 전이에 "고도 기반 전이"를 추가해 RECOVERY 판정을 보강하세요.

## 요구사항
- BMP180으로 상대고도(`relAlt`)를 계산합니다.
- FLIGHT 중 최대고도(`maxRelAlt`)를 계속 갱신합니다.
- `(maxRelAlt - relAlt) > 5.0`이면 RECOVERY로 전이합니다.
- 시간 조건(10초)도 백업으로 유지합니다.

## 구현 방향
template.ino의 `TODO 1 -> TODO 2 -> TODO 3 -> TODO 4 -> TODO 5 -> TODO 6` 순서로 진행합니다.
1. P07의 `alt0`, `relAlt` 계산 코드를 먼저 가져옵니다.
2. `maxRelAlt` 전역변수를 두고 FLIGHT 중 최대값을 갱신합니다.
3. 고도 전이 조건 `maxRelAlt - relAlt > 5.0`을 먼저 검사합니다.
4. 다음으로 시간 조건(10초)을 백업 조건으로 검사합니다.
5. 전이 시 `reason`을 `ALT` 또는 `TIME`으로 로그에 남깁니다.
