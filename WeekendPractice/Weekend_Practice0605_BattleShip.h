#include <iostream>
#include <vector>
#include <string>

const int BOARD_SIZE = 10; // 10x10 크기의 게임 판
const int MAX_TURNS = 30;  // 플레이어에게 주어진 최대 포격 횟수

//조체
struct Ship {
    std::string name;                             // 함선 이름 (항공모함, 전함 등)
    int size;                                     // 함선이 차지하는 칸 수 (크기)
    int hitCount = 0;                             // 현재까지 맞은 횟수
    std::vector<std::pair<int, int>> coordinates; // 함선이 배치된 맵 상의 (x, y) 좌표 목록

    // 함선의 격침 여부를 반환하는 함수 (맞은 횟수가 크기와 같아지면 격침)
    bool isSunk() const {
        return hitCount >= size;
    }
};


class BattleShipGame {
private:
    char playerBoard[BOARD_SIZE][BOARD_SIZE];   // 플레이어 화면: 포격 기록 표시 ('O': 명중, 'X': 실패, '.': 미탐색)
    char computerBoard[BOARD_SIZE][BOARD_SIZE]; // 컴퓨터 화면: 실제 적 함선의 위치 저장 ('S': 함선, '.': 바다)
    std::vector<Ship> ships;                     // 게임에 참여하는 함선들의 목록
    int remainingTurns;                         // 남은 포격 횟수

  
   //메서드
   //playerBoard와 computerBoard의 모든 칸을 아직 탐색하지 않은 바다 상태인 '.'으로 채움
  
    void initBoards();

    
    //게임에 사용할 함선 목록 등록
    //규격에 맞는 4척의 함선(항공모함:5, 전함:4, 순양함:3, 구축함:2)의 이름과 크기 설정 후 ships 벡터에 삽입
    
    void initShips();

    
    //함선 랜덤 배치
    //등록된 모든 함선을 순회하며, 맵 상에 겹치지 않고 배치될 때까지 rand()를 활용해 무작위 좌표와 방향을 설정함
    
    void placeShipsRandomly();

    //
    //@brief 함선 배치 가능 여부 검증 메서드
    //@param startX 배치를 시작할 행 좌표
    //@param startY 배치를 시작할 열 좌표
    //@param size   배치할 함선의 크기
    //@param direction 배치 방향 (0: 가로, 1: 세로)
    //@return true  배치 가능 (경계를 벗어나지 않고 다른 함선과 겹치지 않음)
    //@return false 배치 불가능 (경계 초과 또는 기존 함선과 충돌)
    //
    bool canPlaceShip(int startX, int startY, int size, int direction);

    //
    //게임 보드 화면 출력
    //출력하고자 하는 2차원 문자 배열
    //상/좌측 인덱스 가이드를 포함하여 현재 보드 상태를 그리드 형태로 콘솔에 출력함
    //
    void printBoard(char board[BOARD_SIZE][BOARD_SIZE]);

    //
    //현재 생존한 적 함선 수 계산
    //*벡터를 순회하며 아직 격침되지 않은 함선의 총 개수를 반환함
    //남은 함선의 수
    //
    int getRemainingShipsCount();

    
     //명중 시 함선 상태 업데이트 및 격침 판정
     //플레이어가 포격한 행 좌표
     //플레이어가 포격한 열 좌표
     //피격된 좌표가 어떤 함선에 속하는지 판별하여 hitCount를 누적고, 침몰 시 격침 메시지를 출력
    
    void checkHitShip(int x, int y);

public:
    
    //생성자
    //난수 시드(srand)를 설정, 턴 수 초기화 및 보드 세팅, 함선 랜덤 배치를 순차적으로 수행
 
    BattleShipGame();

   //
   //메인 루프
   //최종 승패 결과와 컴퓨터의 배치도를 공개
   //
    void play();
};