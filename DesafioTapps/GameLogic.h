#pragma once
#include "ParseBoardValues.h"
#include "Property.h"
#include "Player.h"
#include <functional>

class GameLogic
{
private:
	std::vector<Property*> properties;
	std::vector<Player*> players;

	const int numberOfRounds = 300;
	const int cashPerLap = 100;
	const int dieFaces = 6;
	const int roundsTimeout = 1000;
	ParseBoardValues parser;

	//Game Statistics
	int impulsivePlayerVitories;
	int demandingPlayerVictories;
	int causiousPlayerVictories;
	int randomPlayerVictories;

	std::vector<int> roundsPerGame;

public:
	GameLogic();
	~GameLogic();

	void MainLoop();
	void RemovePlayerProperties(Player*);
	void ApplyPlayerBehaviour(Player*, Property*);
	
	bool CheckVictory();

	Player* SelectWinner();
	void ClearGameRound();
};

