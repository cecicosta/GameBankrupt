#pragma once
#include "Player.h"
class Property {
private:
	int sellingValue;
	int rentValue;
	int ownerId;
	bool isSold;
public:
	Property(int sellingValue, int rentValue);
	Property();

	int GetRentValue();
	int GetSellingValue();
	int GetOwnerId();
	void SetForSelling();

	bool Buy(Player* player);
	bool Rent(Player* player, Player* owner);

	bool IsSold();
};


