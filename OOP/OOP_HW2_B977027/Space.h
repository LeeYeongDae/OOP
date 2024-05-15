#pragma once
#include "GameObject.h"
#include "GameManager.h"

class Space :
    public GameObject
{
    int bombCount;
    int isStated;	// 0 = Mimicked, 1 = Flag, 2 = Opened
    bool isBomb;
    bool checked;

    void setShapetoState()
    {
        switch (isStated)
        {
        case 0:
            setShape('O');
            break;
        case 1:
            setShape('#');
            break;
        case 2:
            if (isBomb) setShape('%');
            else if (bombCount == 0) setShape(' ');
            else
            {
                char counted = bombCount + '0';
                setShape(counted);
            }
            checked = true;
            break;
        }
    }

public:
    Space(int x = 0, int y = 0) 
        : GameObject('O', x, y), bombCount(0), isStated(0), isBomb(false), checked(false) {}

    void update() override  { setShapetoState(); }

    void openSpace(Space* spaces)
    {
        setState(2);
        update();
        if (getbombCount() == 0)
        {
            int i = getNum();
            if (i - 11 >= 0 && spaces[i].getPos().y - 1 == spaces[i - 11].getPos().y && spaces[i - 11].getState() == 0)
                spaces[i - 11].openSpace(spaces);
            if (i - 10 >= 0 && spaces[i - 10].getState() == 0)
                spaces[i - 10].openSpace(spaces);
            if (i - 9 >= 0 && spaces[i].getPos().y - 1 == spaces[i - 9].getPos().y && spaces[i - 9].getState() == 0)
                spaces[i - 9].openSpace(spaces);
            if (i - 1 >= 0 && spaces[i].getPos().y == spaces[i - 1].getPos().y && spaces[i - 1].getState() == 0)
                spaces[i - 1].openSpace(spaces);
            if (i + 1 < 100 && spaces[i].getPos().y == spaces[i + 1].getPos().y && spaces[i + 1].getState() == 0)
                spaces[i + 1].openSpace(spaces);
            if (i + 9 < 100 && spaces[i].getPos().y + 1 == spaces[i + 9].getPos().y && spaces[i + 9].getState() == 0)
                spaces[i + 9].openSpace(spaces);
            if (i + 10 < 100 && spaces[i + 10].getState() == 0)
                spaces[i + 10].openSpace(spaces);
            if (i + 11 < 100 && spaces[i].getPos().y + 1 == spaces[i + 11].getPos().y && spaces[i + 11].getState() == 0)
                spaces[i + 11].openSpace(spaces);
        }
    }

    int getState() { return isStated; }

    void setState(int state) { this->isStated = state; }

    int getNum() { return (getPos().x / 2 + getPos().y * 10); }

    auto getBomb() { return isBomb; }

    void setBomb(bool bomb) { this->isBomb = bomb; }

    int getbombCount() { return bombCount; }

    void addbombCount() { this->bombCount++; }
};

