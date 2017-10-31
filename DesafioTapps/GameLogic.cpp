#include "stdafx.h"
#include "GameLogic.h"

#include "ParseBoardValues.h"
#include "Player.h"
#include "Property.h"

#include <numeric>
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
		CreatePlayers();

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

				//Pay the property rent to the owner
				if (property->IsSold()) {
					property->Rent(player, GetPlayer(property->GetOwnerId()));
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
		playersVitories[winner->GetId()]++;
		roundsPerGame.push_back(rounds);

		ClearGameRound();
	}

	PrettyPrintStatistics();
}


void GameLogic::CreatePlayers()
{
	Player *player1 = new Player(0, Player::Behaviour::IMPULSIVE);
	Player *player2 = new Player(1, Player::Behaviour::DEMANDING);
	Player *player3 = new Player(2, Player::Behaviour::CAUTIOUS);
	Player *player4 = new Player(3, Player::Behaviour::RANDOM);
	players = vector<Player*>{ player1, player2, player3, player4 };
	std::random_shuffle(players.begin(), players.end());
	for each (Player* p in players) {
		p->AddCash(300);
	}
}



Player* GameLogic::GetPlayer(int id) {
	vector<Player*>::iterator it = std::find_if(players.begin(), players.end(), [&id](Player *p) {return p->GetId() == id; });
	return *(it._Ptr);
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
	case Player::Behaviour::IMPULSIVE:
		property->Buy(player);
		break;
	case Player::Behaviour::DEMANDING:
		if (property->GetRentValue() > 50)
			property->Buy(player);
		break;
	case Player::Behaviour::CAUTIOUS:
		if (player->GetAmountOfCash() - property->GetSellingValue() >= 80)
			property->Buy(player);
		break;
	case Player::Behaviour::RANDOM:
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

	//Select the one with more cash at the end and which position was prior the next with same cash
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

void GameLogic::PrettyPrintStatistics()
{
	//Temporarily create the players to associate they behaviour and ids 
	CreatePlayers();

	int bestScored = 0;
	//Print statistics
	std::cout << "Distribuicao de Vitorias:" << endl;
	for (int i = 0; i < playersVitories.size(); i++) {
		std::cout << "Jogador " << Player::GetBehaviourString(GetPlayer(i)->behavior) << ": " << (100 * playersVitories[i]) / numberOfRounds << "%" << endl;
		bestScored = playersVitories[i] > playersVitories[bestScored] ? i : bestScored;
	}

	//Players com melhor pontuação
	std::cout << "Comportamento(s) com Mais Vitorias:" << endl;
	for (int i = 0; i < playersVitories.size(); i++)
	{
		if (playersVitories[bestScored] == playersVitories[i]) {
			std::cout << Player::GetBehaviourString(GetPlayer(i)->behavior) << endl;
		}
	}

	int roundsTimeout = this->roundsTimeout;
	int numberOfTimeouts = std::count_if(roundsPerGame.begin(), roundsPerGame.end(), [&roundsTimeout](int rounds) {return rounds >= roundsTimeout; });
	float averageOfRounds = (float)std::accumulate(roundsPerGame.begin(), roundsPerGame.end(), 0) / (float)roundsPerGame.size();

	std::cout << "Media de rodadas por partida: " << averageOfRounds << endl;

	std::cout << "Partidas terminadas com Timeout: " << numberOfTimeouts << endl;

	ClearGameRound();
}
