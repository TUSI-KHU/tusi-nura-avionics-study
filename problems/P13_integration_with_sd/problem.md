# P13 - 기본 기능 + SD 통합

## 문제 설명
P10 코드에 P12의 SD 로깅 함수를 결합하세요.

## 요구사항
- 상태머신(BOOT~RECOVERY)은 기존처럼 동작해야 합니다.
- SD 실패 시에도 상태머신은 계속 동작해야 합니다.
- 100ms마다 `millis,state,accMag,relAlt`를 기록합니다.

## 구현 방향
template.ino의 `TODO 1 -> TODO 2 -> TODO 3 -> TODO 4` 순서로 진행합니다.
1. P10 `answer.ino`를 복사해 기본 코드로 사용합니다.
2. P12에서 만든 `setupLogging()`과 `logData()`를 추가합니다.
3. setup 마지막에 `setupLogging()`을 호출합니다.
4. loop 마지막에 `logData()`를 호출합니다.
5. SD 관련 실패는 `logEnabled`로 막고 상태머신 코드와 분리합니다.
