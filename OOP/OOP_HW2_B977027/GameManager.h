#pragma once
#include <iostream>
#include <conio.h>
#include <cstring>
#include <string>
#include <ctime>
#include <vector>
#include "GameObject.h"
#include "Utils.h"
#include "Screen.h"
#include "Player.h"
#include "Space.h"
#include "InputSystem.h"

#define SPACE_COUNT 100

using namespace std;

class GameManager
{
	Screen& screen;
	Player& player;
	int n_bombs;
	Space* spaces;
	InputSystem& input;
	int opened;
	int flaged;
	bool isCleared;
	bool isOver;

	void initSpace()
	{
		for (int i = 0; i < SPACE_COUNT; i++)
		{
			spaces[i].setScreen(&screen);
			Position pos = spaces[i].getPos();
			pos.x = (i % 10) * 2;
			pos.y = i / 10;
			spaces[i].setPos(pos);
		}
	}

	void initBomb()
	{
		int bombnum;
		for (int i = 0; i < n_bombs; i++)
		{
			bombnum = rand() % 100;
			Position pos = spaces[bombnum].getPos();
			pos.x = (bombnum % 10) * 2; pos.y = bombnum / 10;
			if (spaces[bombnum].getBomb())
			{
				i--;
				continue;
			}
			spaces[bombnum].setPos(pos);
			spaces[bombnum].setBomb(true);

			//Set the spaces' bombCount
			if (bombnum - 11 >= 0 && spaces[bombnum].getPos().y - 1 == spaces[bombnum - 11].getPos().y)
				spaces[bombnum - 11].addbombCount();
			if (bombnum - 10 >= 0)
				spaces[bombnum - 10].addbombCount();
			if (bombnum - 9 >= 0 && spaces[bombnum].getPos().y - 1 == spaces[bombnum - 9].getPos().y)
				spaces[bombnum - 9].addbombCount();
			if (bombnum - 1 >= 0 && spaces[bombnum].getPos().y == spaces[bombnum - 1].getPos().y)
				spaces[bombnum - 1].addbombCount();
			if (bombnum + 1 < 100 && spaces[bombnum].getPos().y == spaces[bombnum + 1].getPos().y)
				spaces[bombnum + 1].addbombCount();
			if (bombnum + 9 < 100 && spaces[bombnum].getPos().y + 1 == spaces[bombnum + 9].getPos().y)
				spaces[bombnum + 9].addbombCount();
			if (bombnum + 10 < 100)
				spaces[bombnum + 10].addbombCount();
			if (bombnum + 11 < 100 && spaces[bombnum].getPos().y + 1 == spaces[bombnum + 11].getPos().y)
				spaces[bombnum + 11].addbombCount();
		}
	}

	void open()
	{
		Position pos = player.getPos();
		for (int i = 0; i < SPACE_COUNT; i++)
		{
			if (pos.x == spaces[i].getPos().x && pos.y == spaces[i].getPos().y && spaces[i].getState() == 0)
			{
				spaces[i].openSpace(spaces);
				if (spaces[i].getBomb())
				{
					spaces[i].setShape('%');
					gameover();
				}
				opened++;
				if (opened == SPACE_COUNT - n_bombs)
				{
					isCleared = true;
					gameover();
				}
			}
		}
	}

	void flag()
	{
		Position pos = player.getPos();
		for (int i = 0; i < SPACE_COUNT; i++)
		{
			if (pos.x == spaces[i].getPos().x && pos.y == spaces[i].getPos().y)
			{
				if (spaces[i].getState() == 0)
				{
					spaces[i].setState(1);
					spaces[i].update();
					if (spaces[i].getBomb())
						flaged++;
				}
				else if (spaces[i].getState() == 1)
				{
					spaces[i].setState(0);
					spaces[i].update();
					if (spaces[i].getBomb())
						flaged--;
				}
				if (flaged == n_bombs)
				{
					isCleared = true;
					gameover();
				}
			}
		}
	}

	void gameover() 
	{ 
		draw();
		Borland::GotoXY(0, 18);
		if (isCleared) printf("You win!");
		else printf("Game Over");
		isOver = true;
	}

public:
	GameManager(Screen& screen, Player& player, int n_bomb, Space* space, InputSystem& input)
		: screen(screen), player(player), n_bombs(n_bomb), spaces(space), input(input),
			opened(0), flaged(0), isCleared(false), isOver(false) {}

	void initGame()
	{
		player.setScreen(&screen);

		initSpace();
		initBomb();
	}

	void draw()
	{
		screen.clear();
		input.readEveryFrame();

		for (int i = 0; i < SPACE_COUNT; i++)
			spaces[i].draw();

		player.draw();
	}

	void getInput()
	{
		auto pos = player.getPos();
		if (input.getKeyDown(0x57) || input.getKeyDown(VK_UP)) {
			pos.y--;
		}
		else if (input.getKeyDown(0x41) || input.getKeyDown(VK_LEFT)) {
			pos.x -= 2;
		}
		else if (input.getKeyDown(0x53) || input.getKeyDown(VK_DOWN)) {
			pos.y++;
		}
		else if (input.getKeyDown(0x44) || input.getKeyDown(VK_RIGHT)) {
			pos.x += 2;
		}
		player.setPos(pos);

		if (input.getKeyDown(0x46)) flag();
		else if (input.getMouseButtonDown(1)) {
			pos = input.getMousePosition();
			if (pos.x % 2 == 0 && pos.x < 20 && pos.y < 10)
			{
				player.setPos(pos);
				flag();
			}
		}
		if (input.getKeyDown(VK_SPACE)) open();
		else if (input.getMouseButtonDown(0)) {
			pos = input.getMousePosition();
			if (pos.x % 2 == 0 && pos.x < 20 && pos.y < 10)
			{
				player.setPos(pos);
				open();
			}
		}
	}

	bool getOver() { return isOver; }
};

