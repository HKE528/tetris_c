#pragma once
#include<cstdio>
#include<conio.h>
#include<Windows.h>

#define UP 72
#define DOWN 80
#define LEFT 75
#define RIGHT 77
#define SPACE 32
#define WIDTH 10
#define HEIGHT 20

typedef struct _tetris {
	int level;
	int gameover;
	int score;
	int rotation;
	int absX, absY;
	int curX, curY;
	int curBlock;
	int nextBlock;
}Tetris;

