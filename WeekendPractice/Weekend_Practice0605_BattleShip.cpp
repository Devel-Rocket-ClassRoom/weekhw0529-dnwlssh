#include "Weekend_Practice0605_BattleShip.h"
#include <ctime>
#include <iomanip>


using namespace std;

// 생성자 구현
BattleShipGame::BattleShipGame() {
    // 매 실행마다 무작위 배치가 달라지도록 현재 시간을 시드로 설정
    srand(static_cast<unsigned int>(time(NULL)));

    // 초기 포격 횟수 세팅
    remainingTurns = MAX_TURNS;

    // 보드, 함선 목록, 위치 랜덤 배치 함수 호출
    initBoards();
    initShips();
    placeShipsRandomly();
}

// 보드 초기화
void BattleShipGame::initBoards() {
    for (int i = 0; i < BOARD_SIZE; ++i) {
        for (int j = 0; j < BOARD_SIZE; ++j) {
            playerBoard[i][j] = '.';   // '.' : 아직 포격하지 않은 미탐색 지역
            computerBoard[i][j] = '.'; // '.' : 적 함선이 배치되지 않은 빈 바다
        }
    }
}

// 함선 정보 생성 및 등록
void BattleShipGame::initShips() {
    // 초기화 리스트로 함선 4척 정의
    ships = {
        {"항공모함", 5},
        {"전함", 4},
        {"순양함", 3},
        {"구축함", 2}
    };
}

// 맵에 함선 랜덤 배치
void BattleShipGame::placeShipsRandomly() {
    for (auto& ship : ships) {
        bool placed = false;

        // 함선이 정상적으로 배치 완료될 때까지 루프 지속
        while (!placed) {
            // 임의의 시작점(행, 열) 설정
            int startX = rand() % BOARD_SIZE;
            int startY = rand() % BOARD_SIZE;

            // 0: 가로 배치, 1: 세로 배치
            int direction = rand() % 2;

            // 가상 계산 결과가 배치 가능 기준을 충족하는지 검증
            if (canPlaceShip(startX, startY, ship.size, direction)) {
                // 검증 완료 시 함선 크기만큼 맵 데이터를 실제로 수정
                for (int i = 0; i < ship.size; ++i) {
                    // 방향에 따른 좌표 오프셋 가산 연산
                    int currentX = startX + (direction == 0 ? 0 : i);
                    int currentY = startY + (direction == 0 ? i : 0);

                    computerBoard[currentX][currentY] = 'S'; // 'S'hip 기호 기록

                    // 함선 객체 내부의 고유 좌표 추적 리스트에 기록 추가
                    ship.coordinates.push_back({ currentX, currentY });
                }
                placed = true; // 현재 함선 배치 완료 처리 후 while 루프 탈출
            }
        }
    }
}

// 배치 가능 여부 검사
bool BattleShipGame::canPlaceShip(int startX, int startY, int size, int direction) {
    for (int i = 0; i < size; ++i) {
        // 루프 돌며 예정 좌표 연산
        int nextX = startX + (direction == 0 ? 0 : i);
        int nextY = startY + (direction == 0 ? i : 0);

        // 10x10 보드 인덱스 경계값 확인
        if (nextX >= BOARD_SIZE || nextY >= BOARD_SIZE) return false;

        // 배치 공간에 이미 다른 함선이 있는지 검사
        if (computerBoard[nextX][nextY] != '.') return false;
    }
    return true; // 위 예외 조건에 걸리지 않을 경우 배치 가능 판정
}

// 화면 출력
void BattleShipGame::printBoard(char board[BOARD_SIZE][BOARD_SIZE]) {
    // 열 가이드 라인(0~9) 출력
    cout << "   ";
    for (int i = 0; i < BOARD_SIZE; ++i) cout << i << " ";
    cout << "\n";

    // 좌측 행 인덱스 표기와 함께 보드 배열 값들을 순차 출력
    for (int i = 0; i < BOARD_SIZE; ++i) {
        //cout << setw(2) << i << " "; // 최소 2칸은 쓰도록하기
        printf("%2d ",i);
        for (int j = 0; j < BOARD_SIZE; ++j) {
            cout << board[i][j] << " ";
        }
        cout << "\n";
    }
    cout << "\n";
}

// 생존 상태의 함선 카운트
int BattleShipGame::getRemainingShipsCount() {
    int count = 0;
    for (const auto& ship : ships) {
        if (!ship.isSunk()) count++; // 격침 검사 불통과 시 생존 카운트 가산
    }
    return count;
}

// 포격 피격 판정 및 알림
void BattleShipGame::checkHitShip(int x, int y) {
    for (auto& ship : ships) {
        for (const auto& coord : ship.coordinates) {
            // 유저 공격 좌표와 매칭되는 함선 블록 검색
            if (coord.first == x && coord.second == y) {
                ship.hitCount++; // 해당 함선의 누적 피격치 증가
                cout << "[명중] " << ship.name << "을(를) 맞췄습니다!\n";

                // 타격 반영 직후 해당 함선의 라이프 소진 여부 확인
                if (ship.isSunk()) {
                    cout << "[격침] 이 선장의 훌륭한 포격으로 적의 '" << ship.name << "'이(가) 침몰했습니다!\n";
                }
                return; // 탐색 목적을 달성했으므로 연산 조기 종료
            }
        }
    }
}

// 메인 루프 진행
void BattleShipGame::play() {
    cout << "=============================\n";
    cout << "   BATTLE SHIP GAME START    \n";
    cout << "=============================\n\n";

    // 잔여 포격 횟수가 있고, 생존한 적 함선이 존재할 때만 루프 작동
    while (remainingTurns > 0 && getRemainingShipsCount() > 0) {
        cout << "-----------------------------------------\n";
        cout << "남은 포격 횟수: " << remainingTurns << "회 | 남은 적 함선: " << getRemainingShipsCount() << "척\n";
        cout << "-----------------------------------------\n";
        cout << "< 플레이어 지도 (O: 명중, X: 실패, .: 미탐색) >\n";
        printBoard(playerBoard);

        int x, y;
        cout << "공격할 좌표를 입력하세요 (행 열 -> 예: 3 4): ";
        cin >> x >> y;

        // 예외 검사 1: 범위를 이탈한 좌표 필터링
        if (x < 0 || x >= BOARD_SIZE || y < 0 || y >= BOARD_SIZE) {
            cout << "!Warning! 잘못된 좌표입니다! 0부터 " << BOARD_SIZE - 1 << " 사이의 값을 입력해주세요.\n";
            continue; // 기회 소모 없이 루프 재시작
        }

        // 예외 검사 2: 기 입력 좌표 필터링
        if (playerBoard[x][y] == 'O' || playerBoard[x][y] == 'X') {
            cout << "!Warning! 이미 포격했던 좌표입니다. 다른 좌표를 선택하세요.\n";
            continue; // 기회 소모 없이 루프 재시작
        }

        // 유효 입력 확인 시 기회 차감 차감
        remainingTurns--;

        // 컴퓨터 보드의 원본 데이터 확인 후 분기 처리
        if (computerBoard[x][y] == 'S') {
            playerBoard[x][y] = 'O'; // 명중 표식
            checkHitShip(x, y);
        }
        else {
            playerBoard[x][y] = 'X'; // 실패 표식
            cout << "[실패] 허공을 가르는 포격이었습니다.\n";
        }
        cout << "\n";
    }

    //게임 종료 시퀀스
    cout << "=============================\n";
    cout << "          GAME OVER          \n";
    cout << "=============================\n\n";

    // 생존 함선 수가 0이면 최종 플레이어 승리 판정
    if (getRemainingShipsCount() == 0) {
        cout << "축하합니다! 제한 시간 내에 모든 적 함선을 격침하여 승리했습니다!\n\n";
    }
    // 함선이 남았으나 기회가 소진된 경우 패배 판정
    else {
        cout << "패배했습니다... 탄약이 모두 소진되었습니다. \n\n";
    }

    // 결과 정답지 개념의 컴퓨터 실제 배치도 최종 오픈
    cout << "< 적 함선의 실제 배치도 (S: 함선 위치) >\n";
    printBoard(computerBoard);
}