
#include <stdlib.h>
#include "MovingWindow.h"

#define  RIGHTBOTTOM 0
#define  RIGHTTOP    1
#define  LEFTTOP     2
#define  LEFTBOTTOM  3
#define  PIX 2

MovingWindow::MovingWindow():
width(100),
height(100)
{
	direction = rand() % 4;
}

void MovingWindow::Init(HWND h) {
	hNotepad = h;
	GetWindowRect(hNotepad, &r);
}

void MovingWindow::Mov() {
	if (direction == RIGHTBOTTOM){
		if (r.bottom <= GetSystemMetrics(SM_CYSCREEN) && r.right <= GetSystemMetrics(SM_CXSCREEN))
			MoveWindow(hNotepad, r.left + PIX, r.top + PIX, width, height, true);
		else direction = rand() % 4;
	}
	else if (direction == RIGHTTOP){
		if (r.top >= 0 && r.right <= GetSystemMetrics(SM_CXSCREEN))
			MoveWindow(hNotepad, r.left + PIX, r.top - PIX, width, height, true);
		else direction = rand() % 4;
	}
	else if (direction == LEFTTOP){
		if (r.top >= 0 && r.left >= 0)
			MoveWindow(hNotepad, r.left - PIX, r.top - PIX, width, height, true);
		else direction = rand() % 4;
	}
	else if (direction == LEFTBOTTOM){
		if (r.bottom <= GetSystemMetrics(SM_CYSCREEN) && r.left >= 0)
			MoveWindow(hNotepad, r.left - PIX, r.top + PIX, width, height, true);
		else direction = rand() % 4;
	}
}

void MovingWindow::CollisionBoxes(std::vector<std::shared_ptr<MovingWindow> >& v) {
	RECT rt, t;
	bool flag;
	int tmp;

	GetWindowRect(hNotepad, &r);
	rt = r;

	do{
		flag = false;
		if (direction == RIGHTBOTTOM){ rt.left += PIX; rt.top += PIX; rt.bottom += PIX; rt.right += PIX; }
		else if (direction == RIGHTTOP){ rt.left += PIX; rt.top -= PIX; rt.bottom -= PIX; rt.right += PIX; }
		else if (direction == LEFTTOP){ rt.left -= PIX; rt.top -= PIX; rt.bottom -= PIX; rt.right -= PIX; }
		else if (direction == LEFTBOTTOM){ rt.left -= PIX; rt.top += PIX; rt.bottom += PIX; rt.right -= PIX; }


		for (unsigned int i = 0; i < v.size(); ++i){
			if (v[i]->hNotepad == this->hNotepad)
				continue;
			GetWindowRect(v[i]->hNotepad, &v[i]->r);
			if (IntersectRect(&t, &rt, &v[i]->r)){
				do{
					tmp = rand() % 4;
				} while (tmp == direction);
				direction = tmp;
				flag = true;
				break;
			}
		}
	} while (flag);
	Mov();
}

void MovingWindow::StartingPosition(std::vector<std::shared_ptr<MovingWindow> >& v) {
	for (unsigned int i = 0; i < v.size(); ++i) {
		MoveWindow(v.at(i)->hNotepad, i * (width + 50), i * (height + 50), 100, 100, true);
	}
}

MovingWindow::~MovingWindow() {
	SendMessage(hNotepad, WM_CLOSE, 0, 0);
}


