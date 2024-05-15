#pragma once
#include <iostream>
#include "Utils.h"
#include "Screen.h"

using namespace std;


class GameObject
{
	Position pos;
	char* shape;
	Dimension dim;
	Screen* screen;

public:
	GameObject(char shape, int x, int y)
		: pos(x, y), shape(nullptr), dim(1, 1)
	{
		this->shape = (char*)new char[dim.size() + 1];
		this->shape[0] = shape;
		this->shape[dim.size()] = '\0';
	}

	virtual ~GameObject() {
		delete[] shape;
	}

	virtual void update() {}

	virtual void draw() {screen->draw(pos, shape[0]);}

	Position getPos() const { return pos;  }

	void setPos(const Position& pos)
	{
		if (screen->isValidPos(pos) == false)
			return;
		this->pos.x = pos.x; this->pos.y = pos.y;
	}

	char getShape() const { return shape[0]; }

	void setShape(char shape) { this->shape[0] = shape; }

	auto getScreen() const { return screen;}

	void setScreen(Screen* screen) { this->screen = screen; }
};

