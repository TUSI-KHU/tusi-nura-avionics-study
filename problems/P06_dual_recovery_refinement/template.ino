// 시작 방법:
// 1) P05 answer.ino를 복사합니다.
// 2) 아래 TODO를 따라 ALT를 먼저 보는 RECOVERY를 추가합니다.

float maxRelAlt = 0;

void onFlightEnter() {
  // TODO 1: FLIGHT에 들어갈 때 maxRelAlt 초기화
}

void updateMaxAltitude() {
  // TODO 2: FLIGHT 동안 maxRelAlt 갱신
}

void updateRecoveryState(unsigned long now, unsigned long flightStartMs, float relAlt) {
  // TODO 3: FLIGHT->RECOVERY 상태 바꾸기
  // - ALT 조건 먼저 확인: (maxRelAlt - relAlt) > 5.0
  // - TIME 조건은 백업으로 그다음 확인
  // - reason은 ALT/TIME으로 구분
}
