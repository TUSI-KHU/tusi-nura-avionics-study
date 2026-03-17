# P05 - IMU 값 해석(가속도 크기)

## 문제 설명
원시 가속도 데이터에서 가속도 크기(`mag`)를 계산하고, 임계치와 비교해 이벤트 후보를 출력하세요.

## 요구사항
- 가속도 크기 `mag = sqrt(ax*ax + ay*ay + az*az)`를 계산합니다.
- 계산한 `mag`를 주기 출력합니다.
- `mag > THRESHOLD` 여부를 함께 출력합니다.

## 구현 방향
template.ino의 `TODO 1 -> TODO 2 -> TODO 3` 순서로 진행합니다.
1. P04 코드에서 `ax`, `ay`, `az`를 읽는 부분을 그대로 가져옵니다.
2. `float mag = sqrt(ax*ax + ay*ay + az*az);`를 계산합니다.
3. 임계치 상수 `THRESHOLD`를 선언합니다.
4. `bool isEvent = (mag > THRESHOLD);`로 이벤트 후보를 만듭니다.
5. 50ms 주기로 `[IMU] mag=... event=...` 형식으로 출력합니다.
