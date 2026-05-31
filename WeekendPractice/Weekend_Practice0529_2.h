#pragma once

enum RankNumber
{
	Ace = 1,
	Two ,
	Three,
	Four,
	Five,
	Six,
	Seven,
	Eight,
	Nine,
	Ten,
	
	Jack,
	Queen,
	King,
};

struct Card
{
	RankNumber Rank;
	std::string Suit;
	bool IsDraw;

	Card() 
	{
		Rank = Ace;
		Suit = "";
		IsDraw = false;
	}
	
	Card(RankNumber Num, std::string Shape)
	{
		Rank = Num;
		Suit = Shape;
		IsDraw = false;
	}
};

void Homework02_Run();

void Deck(Card deck[]);

Card DrawCard(Card deck[]);

void CardScore(int& CurrentScore, Card Card, int& AceCount);

void PrintCard(Card Card);