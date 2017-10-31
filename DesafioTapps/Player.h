#pragma once
class Player {
private:
	float cash;
	int position;
	int id;
public:
	
	enum Behavior {
		IMPULSIVE,
		DEMANDING,
		CAUTIOUS,
		RANDOM
	};
	Behavior behavior;
	
	Player(int id, Behavior behavior);

	int GetId();
	int GetCurrentPosition();
	float GetAmountOfCash();
	void AddCash(float amount);
	void SetNewPosition(int position);

	bool Pay(float value);
	bool IsBankupt();
	
};