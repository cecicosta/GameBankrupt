#include "stdafx.h"
#include "Property.h"


Property::Property(int sellingValue, int rentValue) :
	sellingValue(sellingValue), rentValue(rentValue), isSold(false), ownerId(-1){ 
}

Property::Property()
{
}

int Property::GetRentValue()
{
	return rentValue;
}

int Property::GetSellingValue()
{
	return sellingValue;
}

int Property::GetOwnerId()
{
	return ownerId;
}

void Property::SetForSelling()
{
	isSold = false;
	ownerId = -1;
}

bool Property::Buy(Player* player)
{
	if (IsSold())
		return false;

	if (player->GetAmountOfCash() - GetSellingValue() < 0)
		return false;

	player->Pay(sellingValue);
	ownerId = player->GetId();
	isSold = true;

	return true;
}

bool Property::Rent(Player* player, Player* owner)
{
	if (!IsSold())
		return false;

	player->Pay(rentValue);
	owner->AddCash(rentValue);

	return true;
}

bool Property::IsSold()
{
	return isSold;
}


