#ifndef BATTLESHIP_GAME_H
#define BATTLESHIP_GAME_H

#include <iostream>
#include <vector>
#include <string>

// 전역 상수 선언
const int BOARD_SIZE = 10;
const int MAX_TURNS = 30;

// 함선 정보 구조체
struct Ship {
    std::string name;
    int size;
    int hitCount = 0;
    std::vector<std::pair<int, int>> coordinates; // 함선이 차지하는 좌표 목록

    bool isSunk() const {
        return hitCount >= size;
    }
};

// 게임 관리 클래스
class BattleShipGame {
private:
    char playerBoard[BOARD_SIZE][BOARD_SIZE];   // 플레이어가 보는 화면 (공격 기록)
    char computerBoard[BOARD_SIZE][BOARD_SIZE]; // 컴퓨터의 실제 함선 배치도
    std::vector<Ship> ships;
    int remainingTurns;

    // 내부 헬퍼 메서드
    void initBoards();
    void initShips();
    void placeShipsRandomly();
    bool canPlaceShip(int startX, int startY, int size, int direction);
    void printBoard(char board[BOARD_SIZE][BOARD_SIZE]);
    int getRemainingShipsCount();
    void checkHitShip(int x, int y);

public:
    BattleShipGame(); // 생성자
    void play();      // 게임 실행 루프
};

#endif // BATTLESHIP_GAME_H