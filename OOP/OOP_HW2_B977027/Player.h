#pragma once
#include <conio.h>
#include "GameObject.h"

class Player :
    public GameObject
{
public:
    Player(int x, int y) : GameObject('>', x, y) {}

	void draw() override
	{
		//GameObject::draw();
		getScreen()->draw(getPos() + Position{ 1, 0 }, '<');
	}
    
};

