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
