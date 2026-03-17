# P02 - SAFE/ARMED 버튼 + 버저

## 문제 설명
버튼으로 `SAFE`와 `ARMED` 상태를 전환하고, 상태가 바뀔 때 버저로 알림음을 출력하세요.

## 요구사항
- 상태를 `SAFE`, `ARMED`로 정의합니다.
- 버튼 핀은 `INPUT_PULLUP` 방식으로 설정해야 합니다.
- 디바운싱은 하지 않습니다.
- 버튼을 3초 이상 누르면 상태가 한 번 바뀌어야 합니다.
- `ARMED` 상태일 때만 LED를 켭니다. (`SAFE`에서는 LED를 끕니다.)
- 상태가 바뀔 때마다 버저를 짧게 1회 울립니다.

## 구현 방향
template.ino의 `TODO 1 -> TODO 2 -> TODO 3` 순서로 진행합니다.
1. 버튼 핀을 `pinMode(BUTTON_PIN, INPUT_PULLUP)`으로 설정합니다.
2. 버튼이 눌린 시각(`pressStartMs`)을 저장하고, 3초 이상 눌렸는지 검사합니다.
3. 한 번 상태가 바뀌면 버튼을 뗄 때까지 다시 바뀌지 않게 `holdConsumed` 변수를 사용합니다.
4. 상태가 바뀌면 `beepOnce(100)`을 호출합니다.
5. `state == ARMED`면 LED `HIGH`, 아니면 `LOW`로 출력합니다.
