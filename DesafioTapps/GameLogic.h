#pragma once
#include "ParseBoardValues.h"
#include "Property.h"
#include "Player.h"

class GameLogic
{
private:
	std::vector<Property*> properties;
	std::vector<Player*> players;

	const int numberOfRounds = 300;
	const int cashPerLap = 100;
	const int dieFaces = 6;
	const int roundsTimeout = 1000;
	const int initialPlayerCash = 300;
	ParseBoardValues parser;

	//Game Statistics
	vector<int> playersVitories{0,0,0,0};
	std::vector<int> roundsPerGame;

public:
	GameLogic();
	~GameLogic();

	void MainLoop();
	void CreatePlayers();
	Player* GetPlayer(int id);
	void RemovePlayerProperties(Player*);
	void ApplyPlayerBehaviour(Player*, Property*);
	
	bool CheckVictory();

	Player* SelectWinner();
	void ClearGameRound();

	void PrettyPrintStatistics();
};

