#include "stdafx.h"
#include "Player.h"


Player::Player(int id, Behavior behavior): cash(0), position(-1)
{
	this->behavior = behavior;
	this->id = id;
}

int Player::GetId()
{
	return id;
}

void Player::AddCash(float amount)
{
	cash += amount;
}

float Player::GetAmountOfCash()
{
	return cash;
}

int Player::GetCurrentPosition()
{
	return position;
}

void Player::SetNewPosition(int position)
{
	this->position = position;
}

bool Player::Pay(float amount)
{
	bool enoughCash = cash - amount >= 0;
	cash = cash - amount;
	
	return enoughCash;
}

bool Player::IsBankupt()
{
	return GetAmountOfCash() < 0;
}

