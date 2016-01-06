#pragma once
#include <vector>
#include <iostream>
#include <memory>
#include <windows.h>


class MovingWindow
{
	int	width;
	int height;
	RECT r;
	int direction;
	void Mov();
public:
	HWND hNotepad;
	MovingWindow();
	~MovingWindow();
	void StartingPosition(std::vector<std::shared_ptr<MovingWindow> >& v);
	void CollisionBoxes(std::vector<std::shared_ptr<MovingWindow> >&);
	void Init(HWND);
};

