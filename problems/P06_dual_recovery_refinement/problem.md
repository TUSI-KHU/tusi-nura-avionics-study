# P06 - 이중 RECOVERY 조건 다듬기

## 문제 설명
P05 상태머신에 고도 기반 RECOVERY를 추가합니다. 시간 조건은 백업으로 두고, 고도 하강 조건을 먼저 확인합니다.

## 요구사항
- `maxRelAlt`를 FLIGHT 동안 갱신합니다.
- `FLIGHT -> RECOVERY` 먼저 볼 조건: `(maxRelAlt - relAlt) > 5.0`, reason=`ALT`
- 백업조건: FLIGHT 10초 경과 시 reason=`TIME`
- 두 조건 확인 순서는 `ALT 먼저, TIME 나중`으로 고정합니다.

## 구현 방향
template.ino의 TODO 순서로 진행하세요.
1. FLIGHT 진입 시 `maxRelAlt = relAlt`로 초기화합니다.
2. 센서 업데이트에서 `maxRelAlt` 최고값 추적을 추가합니다.
3. `updateRecoveryState()`에서 ALT를 먼저, TIME을 나중에 확인합니다.
