#include"Tetris.h"

void Gotoxy(int x, int y)
{
	COORD pos = { x, y };

	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void RemoveCursor()
{
	CONSOLE_CURSOR_INFO curInfo;
	curInfo.bVisible = 0;
	GetConsoleCursorInfo(STD_OUTPUT_HANDLE), & curInfo);
}