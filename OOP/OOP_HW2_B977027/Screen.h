#pragma once
#include <iostream>
#include "Utils.h"

using namespace std;

class Screen
{
	char* lines;
	int n_rows;
	int n_cols;

	int pos2offset(int x, int y, int n_cols) const
	{
		return y * n_cols + x;
	}

public:
	Screen(int n_cols, int n_rows)
		: n_rows(n_rows), n_cols(n_cols),
		lines(new char[n_rows * n_cols + 1])
	{
		Borland::Initialize();
		clear();
	}

	virtual ~Screen() { delete[] lines; }

	void clear()
	{
		memset(lines, ' ', n_rows * n_cols);
	}

	void draw(const Position& pos, char shape)
	{
		int offset = pos2offset(pos.x, pos.y, n_cols);

		lines[offset] = shape;
	}

	void render()
	{
		Borland::GotoXY(0, 0);
		for (int i = 0; i < n_rows; i++)
			lines[i * n_cols + n_cols-1] = '\n';
		lines[n_rows * n_cols] = '\0';
		printf("%s", lines);
	}

	bool isValidPos(const Position& pos) const
	{
			return (pos.x >= 0 && pos.x < n_cols - 1
				 && pos.y >= 0 && pos.y < n_rows - 1);
	}
};

