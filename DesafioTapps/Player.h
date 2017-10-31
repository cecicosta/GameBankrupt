#pragma once
#include <string>
class Player {
private:
	float cash;
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
	float GetAmountOfCash();
	void AddCash(float amount);
	void SetNewPosition(int position);

	bool Pay(float value);
	bool IsBankupt();

	static std::string GetBehaviourString(Behaviour behaviour);
	
};