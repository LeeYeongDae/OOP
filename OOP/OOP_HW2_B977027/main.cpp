#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <cstring>
#include <string>
#include <ctime>
#include <vector>
#include "GameManager.h"
#include "GameObject.h"
#include "Utils.h"
#include "Screen.h"
#include "Player.h"
#include "Space.h"
#include "InputSystem.h"

#define SPACE_COUNT 100

using namespace std;

int main()
{

	Screen screen(21, 11);
	InputSystem input;

	srand((unsigned int)time(NULL));

	int n_bombs = rand() % 11 + 10;

	Player player{ 0, 0 };
	Space spaces[SPACE_COUNT];

	GameManager gamemanager(screen, player, n_bombs, spaces, input);

	gamemanager.initGame();

	while (!(gamemanager.getOver()))
	{
		gamemanager.draw();

		gamemanager.getInput();

		screen.render();
	}
	
	return 0;
}