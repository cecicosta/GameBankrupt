#pragma once
#include "Player.h"
class Property {
private:
	float sellingValue;
	float rentValue;
	int ownerId;
	bool isSold;
public:
	Property(float sellingValue, float rentValue);
	Property();

	float GetRentValue();
	float GetSellingValue();
	int GetOwnerId();
	void SetForSelling();

	bool Buy(Player* player);
	bool Rent(Player* player, Player* owner);

	bool IsSold();
};


