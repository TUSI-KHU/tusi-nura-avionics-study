# P11 - SD 카드 기본 동작 확인

## 문제 설명
SD 카드가 정상 동작하는지 가장 작은 단계로 확인하세요.

## 요구사항
- `SD.begin(CS_PIN)`으로 초기화합니다.
- `test.txt` 파일을 열어 한 줄 작성합니다.
- 성공/실패를 시리얼로 출력합니다.

## 구현 방향
template.ino의 `TODO 1 -> TODO 2 -> TODO 3` 순서로 진행합니다.
1. `setup()`에서 `SD.begin(SD_CS_PIN)`으로 초기화합니다.
2. 실패하면 `[ERR]`를 출력하고 `return` 합니다.
3. 성공하면 `SD.open("test.txt", FILE_WRITE)`로 파일을 엽니다.
4. 한 줄 작성 후 `close()`합니다.
5. 끝에 `[OK]`를 출력해 성공을 확인합니다.
