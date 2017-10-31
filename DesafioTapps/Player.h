#pragma once
#include <string>
class Player {
private:
	int cash;
	int position;
	int id;
public:
	
	enum Behaviour {
		IMPULSIVE = 0,
		DEMANDING,
		CAUTIOUS,
		RANDOM
	};
	Behaviour behavior;
	
	Player(int id, Behaviour behavior);

	int GetId();
	int GetCurrentPosition();
	int GetAmountOfCash();
	void AddCash(int amount);
	void SetNewPosition(int position);

	bool Pay(int value);
	bool IsBankupt();

	static std::string GetBehaviourString(Behaviour behaviour);
	
};