#include <windows.h>
#include <stdlib.h>
#include <time.h>
#include <vector>
#include <memory>
#include <iostream>
#include "resource.h"
#include "MovingWindow.h"
#define COUNTWIN 11

BOOL CALLBACK DlgProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpszCmdLine, int nCmdShow)
{
	srand((unsigned)time(0));
	return DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, DlgProc);
}

std::vector<std::shared_ptr<MovingWindow> > v;

BOOL CALLBACK EnumWindowProc(HWND hWnd, LPARAM lParam)
{
	std::shared_ptr<MovingWindow> mw(new MovingWindow);
	TCHAR caption[MAX_PATH] = { 0 }, classname[100] = { 0 };
	GetClassName(hWnd, classname, 100);
	GetWindowText(hWnd, caption, MAX_PATH);

	if (!lstrcmp(classname, TEXT("Notepad")) && !lstrcmp(caption, TEXT("Безымянный — Блокнот"))){
		mw->Init(hWnd);
		v.push_back(mw);
	}
	return TRUE;
}

BOOL CALLBACK DlgProc(HWND hWnd, UINT message, WPARAM wp, LPARAM lp)
{
	const unsigned int MY_TIMER_1 = 10;
	const unsigned int MY_TIMER_2 = 20;

	switch (message)
	{
	case WM_CLOSE:
		EndDialog(hWnd, 0);
		return TRUE;
	case  WM_INITDIALOG:
		SetClassLong(hWnd, GCL_HICON, LONG(LoadIcon(GetModuleHandle(0), MAKEINTRESOURCE(IDI_ICON1))));
		for (int i = 0; i < COUNTWIN; ++i) {
			ShellExecute(0, TEXT("open"), TEXT("notepad.exe"), NULL, 0, SW_SHOW);
		}
		SetTimer(hWnd, MY_TIMER_1, 500, NULL);
		return TRUE;
	case WM_TIMER:
		switch (wp){
		case MY_TIMER_1:
			KillTimer(hWnd, MY_TIMER_1);
			EnumWindows(EnumWindowProc, (LPARAM)hWnd);
			BringWindowToTop(hWnd);
			v[0]->StartingPosition(v);
			SetTimer(hWnd, MY_TIMER_2, 10, NULL);
			break;
		case MY_TIMER_2:
			for (unsigned int i = 0; i < v.size(); ++i) {
				v[i]->CollisionBoxes(v);
			}
			break;
		}
		return TRUE;
	}
	return FALSE;
}