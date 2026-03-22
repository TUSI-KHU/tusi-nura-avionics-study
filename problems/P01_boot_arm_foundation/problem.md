# P01 - BOOT/SAFE/ARMED 기초 구성

## 문제 설명
플라이트 컴퓨터에 필요한 가장 기본 상태머신을 만듭니다. BOOT에서는 LED가 깜빡이고, SAFE에서 기다리다가 버튼을 오래 누르면 `SAFE <-> ARMED`가 서로 바뀝니다.

## 요구사항
- `BOOT`, `SAFE`, `ARMED`의 세가지 상태를 정의합니다.
- `BOOT`: 3초 동안 200ms 간격으로 LED를 깜빡인 뒤 `SAFE`로 바꿉니다.
- 버튼(`INPUT_PULLUP`을 사용합니다)을 3초 누르면 `SAFE <-> ARMED`가 바뀝니다.
- 버튼을 계속 누르고 있으면 3초마다 상태가 다시 바뀝니다.
- `ARMED`에서 LED ON, `SAFE`에서 LED OFF를 유지합니다.
- 상태가 바뀔 때 버저를 100ms 울립니다. (template의 `setState()` + `updateBuzzer()`에 기본 포함)
- `delay` 대신 `millis`를 사용해야 합니다.

## 구현 방향
template.ino의 `TODO 1 -> TODO 3` 순서로 진행하세요.
1. BOOT 점멸 후 SAFE로 자동 변경을 구현합니다.
2. 버튼 누른 시간을 재는 변수(`pressStartMs`)로 `SAFE <-> ARMED` 전환을 구현합니다.
3. 상태별 LED 출력을 구현합니다.
