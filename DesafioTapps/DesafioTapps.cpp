// DesafioTapps.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "GameLogic.h"

#include <iostream>
#include <vector>
#include <time.h>

int main()
{
	GameLogic game;
	game.MainLoop();
	system("PAUSE");
    return 0;
}


void DebugPrintPropertyListElements(std::vector<Property*> properties) {
	//Debug purpose: Print all properties selling and rent values
	for each (Property* p in properties)
	{
		std::cout << p->GetSellingValue() << ", " << p->GetRentValue() << ", " << p->IsSold() << endl;
	}
}