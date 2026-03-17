# P07 - BMP180 상대고도 계산

## 문제 설명
BMP180으로 고도를 읽고 시작 시점 기준 상대고도(`relAlt`)를 계산하세요.

## 요구사항
- BMP180 센서를 초기화합니다.
- 시작 후 2초 동안의 고도 평균을 기준고도(`alt0`)로 설정합니다.
- `alt`, `alt0`, `relAlt = alt - alt0`를 주기 출력합니다.
- `delay()` 대신 `millis()`를 사용해야 합니다.

## 구현 방향
template.ino의 `TODO 1 -> TODO 2` 순서로 진행합니다.
1. `bmp.begin()`으로 센서를 초기화하고 실패 시 정지 처리합니다.
2. setup에서 20회 정도 `bmp.readAltitude()`를 읽어 평균 `alt0`를 계산합니다.
3. loop에서 현재 고도 `alt`를 읽고 `relAlt = alt - alt0`를 계산합니다.
4. 100ms 주기로 `alt`, `alt0`, `relAlt`를 출력합니다.
5. 이후 문제에서 재사용할 수 있게 `relAlt` 변수를 전역으로 유지합니다.
