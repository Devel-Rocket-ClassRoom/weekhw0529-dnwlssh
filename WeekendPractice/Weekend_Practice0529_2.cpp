#include <iostream>
#include <stdio.h>
#include <string>
#include "Weekend_Practice0529_2.h"

using namespace std;

void Homework02_Run()
{
	unsigned int Seed = (unsigned int)time(0);	// 테스트용으로 임시로 설정
	srand(Seed);	// 시드값 초기화


	Card deck[52];
	Deck(deck);

	int PlayerScore = 0;
	int PlayerAceCount = 0;
	int DealerScore = 0;
	int DealerAceCount = 0;

	printf("============== Play BlackJack ==============\n\n");

	Card pCard1 = DrawCard(deck);
	CardScore(PlayerScore, pCard1, PlayerAceCount);

	Card pCard2 = DrawCard(deck);
	CardScore(PlayerScore, pCard2, PlayerAceCount);

	Card dCard1 = DrawCard(deck);
	CardScore(DealerScore, dCard1, DealerAceCount);

	Card dCard2 = DrawCard(deck);
	CardScore(DealerScore, dCard2, DealerAceCount);


	printf("플레이어 카드 : ");
	PrintCard(pCard1); PrintCard(pCard2);
	printf("[점수 : %d]\n", PlayerScore);

	printf("딜러 오픈 카드 : ");
	PrintCard(dCard1);
	printf("[ ? ]\n\n");


	bool playerHasBlackjack = (PlayerScore == 21);
	bool dealerHasBlackjack = (DealerScore == 21);

	if (playerHasBlackjack || dealerHasBlackjack) {
		printf("=== 초기 블랙잭 확인 ===\n");
		printf("딜러의 숨겨진 카드 공개: "); PrintCard(dCard1); PrintCard(dCard2);
		printf("(딜러 총점: %d)\n\n", DealerScore);

		if (playerHasBlackjack && dealerHasBlackjack) {
			printf("양쪽 모두 블랙잭! 무승부(Push)입니다.\n");
		}
		else if (playerHasBlackjack) {
			printf("♣♠ 블랙잭! 플레이어 즉시 승리! ♠♣\n");
		}
		else {
			printf("딜러 블랙잭! 플레이어 즉시 패배!\n");
		}
		return;
	}

	while (PlayerScore < 21)
	{
		char Choice;
		printf("카드를 더 받으시겠습니까? ( Hit / Stand ) : \n");
		printf("히트를 원하면 [ H ] 또는 [ h ] 입력하세요.\n");
		cin >> Choice;

		if (Choice == 'H' || Choice == 'h')
		{
			Card newCard = DrawCard(deck);
			CardScore(PlayerScore, newCard, PlayerAceCount);

			printf("뽑은 카드 : ");
			PrintCard(newCard);
			printf("현재 플레이어 점수 : %d\n\n",PlayerScore);
		}
		else
		{
			break;
		}
	}

	if (PlayerScore > 21)
	{
		printf("플레이어 점수 : %d\n", PlayerScore);
		printf("플레이어 버스트! 패배하셨습니다.");
		return;
	}

	printf("===== 딜러 턴 =====\n");
	printf("딜러의 숨겨진 카드 공개 :");
	PrintCard(dCard1); PrintCard(dCard2);
	printf("딜러 총점 : %d\n", DealerScore);

	while (DealerScore < 17)
	{
		printf("딜러가 카드를 한 장 더 뽑습니다.\n");
		Card newCard = DrawCard(deck);
		CardScore(DealerScore, newCard, DealerAceCount);

		printf("딜러가 뽑은 카드: "); PrintCard(newCard);
		printf("(딜러 총점: %d)\n\n", DealerScore);
	}

	printf("=== 최종 결과 ===\n");
	printf("플레이어 점수: %d vs 딜러 점수: %d\n", PlayerScore, DealerScore);

	if (DealerScore > 21) {
		printf("딜러 버스트! 플레이어 승리!\n");
	}
	else if (PlayerScore > DealerScore) {
		printf("플레이어 승리!\n");
	}
	else if (PlayerScore < DealerScore) {
		printf("플레이어 패배!\n");
	}
	else {
		printf("무승부(Push)입니다.\n");
	}
}

void Deck(Card deck[])
{
	std::string Suits[4] = { "♠", "◆", "♥", "♣" };
	int Index = 0;

	for (int i = 0; i < 4; i++)
	{
		for (int j = Ace; j < King; j++)
		{
			deck[Index] = Card(static_cast<RankNumber>(j),Suits[i]);
			Index++;
		}
	}
}

Card DrawCard(Card deck[])
{
	while (true)
	{
		int RandomIndex = rand() % 52;

		if (!deck[RandomIndex].IsDraw)
		{
			deck[RandomIndex].IsDraw = true;
			return deck[RandomIndex];
		}
	}
}

void CardScore(int& CurrentScore, Card Card, int& AceCount)
{
	if (Card.Rank == Ace)
	{
		CurrentScore += 11; 
		AceCount++;
	}
	else if (Card.Rank >= Jack && Card.Rank <= King)
	{
		CurrentScore += 10;
	}
	else
	{
		CurrentScore += Card.Rank;
	}

	while(CurrentScore > 21 && AceCount > 0)
	{
		CurrentScore -= 10;
		AceCount--;
	}
}

void PrintCard(Card Card)
{
	printf("[%s ", Card.Suit.c_str());

	if (Card.Rank == Ace)
	{
		printf("A] ");
	}
	else if (Card.Rank == Jack)
	{
		printf("J] ");
	}
	else if (Card.Rank == Queen)
	{
		printf("Q] ");
	}
	else if (Card.Rank == King)
	{
		printf("K] ");
	}
	else
	{
		printf("%d] ", Card.Rank);

	}
}



