#include "stdafx.h"
#include "GameLogic.h"

#include "ParseBoardValues.h"
#include "Player.h"
#include "Property.h"

#include <time.h>

GameLogic::GameLogic()
{
	//Load file:Parse config file
	parser.Parse();
	srand(time(NULL));
}

GameLogic::~GameLogic()
{
}

void GameLogic::MainLoop()
{
	for (int i = 0; i < numberOfRounds; i++) {

		//Build properties: Get a copy of the properties from the parser
		properties = parser.CopyProperties();

		//Create players
		Player *player1 = new Player(0, Player::Behavior::IMPULSIVE);
		Player *player2 = new Player(1, Player::Behavior::DEMANDING);
		Player *player3 = new Player(2, Player::Behavior::CAUTIOUS);
		Player *player4 = new Player(3, Player::Behavior::RANDOM);
		players = vector<Player*>{ player1, player2, player3, player4 };

		for each (Player *var in players)
		{

		}

		int rounds = 0;
		bool victory = false;
		//Game loop
		while (rounds < roundsTimeout && !victory) {

			//For each player
			for each (Player* player in players)
			{
				if (CheckVictory()) {
					victory = true;
					break;
				}

				if (player->IsBankupt())
					continue;

				//Roll a die
				int dieNumber = rand() % dieFaces + 1;

				int nextLap = (player->GetCurrentPosition() + dieNumber) / properties.size(); //Calculate how many laps this roll complete
				int newPosition = (player->GetCurrentPosition() + dieNumber) % properties.size(); //Calculate the property the player end up

				player->SetNewPosition(newPosition);
				player->AddCash(nextLap * cashPerLap);

				Property* property = properties.at(player->GetCurrentPosition());

				//Play the property rent to the owner
				if (property->IsSold()) {
					property->Rent(player, players.at(property->GetOwnerId()));
				}
				else {
					//Play behavior
					ApplyPlayerBehaviour(player, property);
				}

				//Check if the player lose in this round
				if (player->IsBankupt()) {
					RemovePlayerProperties(player);
				}
			}
			rounds++;
		}

		Player* winner = SelectWinner();
		//Add to staticstics
		roundsPerGame.push_back(rounds);

		ClearGameRound();
	}
}

void GameLogic::RemovePlayerProperties(Player* player)
{
	for each (Property* p in properties)
	{
		if (p->GetOwnerId() == player->GetId()) {
			p->SetForSelling();
		}
	}
}

void GameLogic::ApplyPlayerBehaviour(Player* player, Property* property)
{
	switch (player->behavior) {
	case Player::Behavior::IMPULSIVE:
		property->Buy(player);
		break;
	case Player::Behavior::DEMANDING:
		if (property->GetRentValue() > 50)
			property->Buy(player);
		break;
	case Player::Behavior::CAUTIOUS:
		if (player->GetAmountOfCash() - property->GetSellingValue() >= 80)
			property->Buy(player);
		break;
	case Player::Behavior::RANDOM:
		if (rand() % 2 == 1)
			property->Buy(player);
		break;
	}
}

bool GameLogic::CheckVictory()
{

	return std::count_if(players.begin(), players.end(), [](Player* p) { return !p->IsBankupt(); }) == 1;
}

Player* GameLogic::SelectWinner()
{
	vector<Player*> winners;
	for each (Player* p in players)
	{
		if (!p->IsBankupt()) {
			winners.push_back(p);
		}
	}
	if (winners.size() == 0) //should never happen
		return NULL;

	if (winners.size() == 1) {
		return winners.at(0);
	}

	//Select the one with more cash at the end and which position was the prior the next with same cash
	std::sort(winners.begin(), winners.end(), [](Player* a, Player* b) { return a->GetAmountOfCash() >= b->GetAmountOfCash(); });

	return winners.at(0);
}

void GameLogic::ClearGameRound()
{
	for each (Player* p in players) {
		delete p;
	}
	players.clear();

	for each (Property* p in properties) {
		delete p;
	}
	properties.clear();
}
