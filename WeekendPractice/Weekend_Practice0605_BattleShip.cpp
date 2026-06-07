#include "Weekend_Practice0605_BattleShip.h"
#include <cstdlib>
#include <ctime>
#include <iomanip>

using namespace std;

// 생성자 구현
BattleShipGame::BattleShipGame() {
    srand(static_cast<unsigned int>(time(NULL)));
    remainingTurns = MAX_TURNS;
    initBoards();
    initShips();
    placeShipsRandomly();
}

// 보드 초기화
void BattleShipGame::initBoards() {
    for (int i = 0; i < BOARD_SIZE; ++i) {
        for (int j = 0; j < BOARD_SIZE; ++j) {
            playerBoard[i][j] = '.';   // 미탐색 지역
            computerBoard[i][j] = '.'; // 빈 바다
        }
    }
}

// 함선 정보 등록
void BattleShipGame::initShips() {
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
        while (!placed) {
            int startX = rand() % BOARD_SIZE;
            int startY = rand() % BOARD_SIZE;
            int direction = rand() % 2; // 0: 가로(Horizontal), 1: 세로(Vertical)

            if (canPlaceShip(startX, startY, ship.size, direction)) {
                for (int i = 0; i < ship.size; ++i) {
                    int currentX = startX + (direction == 0 ? 0 : i);
                    int currentY = startY + (direction == 0 ? i : 0);

                    computerBoard[currentX][currentY] = 'S'; // 'S'hip 표시
                    ship.coordinates.push_back({ currentX, currentY });
                }
                placed = true;
            }
        }
    }
}

// 배치 가능 여부 체크
bool BattleShipGame::canPlaceShip(int startX, int startY, int size, int direction) {
    for (int i = 0; i < size; ++i) {
        int nextX = startX + (direction == 0 ? 0 : i);
        int nextY = startY + (direction == 0 ? i : 0);

        if (nextX >= BOARD_SIZE || nextY >= BOARD_SIZE) return false;
        if (computerBoard[nextX][nextY] != '.') return false;
    }
    return true;
}

// 화면 그리기
void BattleShipGame::printBoard(char board[BOARD_SIZE][BOARD_SIZE]) {
    cout << "   ";
    for (int i = 0; i < BOARD_SIZE; ++i) cout << i << " ";
    cout << "\n";

    for (int i = 0; i < BOARD_SIZE; ++i) {
        cout << setw(2) << i << " ";
        for (int j = 0; j < BOARD_SIZE; ++j) {
            cout << board[i][j] << " ";
        }
        cout << "\n";
    }
    cout << "\n";
}

// 생존해 있는 함선 수 계산
int BattleShipGame::getRemainingShipsCount() {
    int count = 0;
    for (const auto& ship : ships) {
        if (!ship.isSunk()) count++;
    }
    return count;
}

// 공격 좌표 피격 판정 및 격침 알림
void BattleShipGame::checkHitShip(int x, int y) {
    for (auto& ship : ships) {
        for (const auto& coord : ship.coordinates) {
            if (coord.first == x && coord.second == y) {
                ship.hitCount++;
                cout << "🎯 [명중] " << ship.name << "을(를) 맞췄습니다!\n";

                if (ship.isSunk()) {
                    cout << "💥 [격침] 이 선장의 훌륭한 포격으로 적의 '" << ship.name << "'이(가) 침몰했습니다!\n";
                }
                return;
            }
        }
    }
}

// 게임 메인 루프 진행
void BattleShipGame::play() {
    cout << "=============================\n";
    cout << "   BATTLE SHIP GAME START    \n";
    cout << "=============================\n\n";

    while (remainingTurns > 0 && getRemainingShipsCount() > 0) {
        cout << "-----------------------------------------\n";
        cout << "▶ 남은 포격 횟수: " << remainingTurns << "회 | 남은 적 함선: " << getRemainingShipsCount() << "척\n";
        cout << "-----------------------------------------\n";
        cout << "< 플레이어 지도 (O: 명중, X: 실패, .: 미탐색) >\n";
        printBoard(playerBoard);

        int x, y;
        cout << "공격할 좌표를 입력하세요 (행 열 -> 예: 3 4): ";
        cin >> x >> y;

        if (x < 0 || x >= BOARD_SIZE || y < 0 || y >= BOARD_SIZE) {
            cout << "❌ 잘못된 좌표입니다! 0부터 " << BOARD_SIZE - 1 << " 사이의 값을 입력해주세요.\n";
            continue;
        }

        if (playerBoard[x][y] == 'O' || playerBoard[x][y] == 'X') {
            cout << "⚠️ 이미 포격했던 좌표입니다. 다른 좌표를 선택하세요.\n";
            continue;
        }

        remainingTurns--;
        if (computerBoard[x][y] == 'S') {
            playerBoard[x][y] = 'O';
            checkHitShip(x, y);
        }
        else {
            playerBoard[x][y] = 'X';
            cout << "🌊 [실패] 허공을 가르는 포격이었습니다.\n";
        }
        cout << "\n";
    }

    cout << "=============================\n";
    cout << "          GAME OVER          \n";
    cout << "=============================\n\n";

    if (getRemainingShipsCount() == 0) {
        cout << "🎉 축하합니다! 제한 시간 내에 모든 적 함선을 격침하여 승리했습니다! 🎉\n\n";
    }
    else {
        cout << "💀 패배했습니다... 탄약이 모두 소진되었습니다. 💀\n\n";
    }

    cout << "< 적 함선의 실제 배치도 (S: 함선 위치) >\n";
    printBoard(computerBoard);
}