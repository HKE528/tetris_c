#include"Tetris.h"
#include <random>
#include <ctime>

std::random_device rd;
std::mt19937 mt(rd());
std::uniform_int_distribution<int> randomBlock(0, 6);
std::uniform_int_distribution<int> randomRotaion(0, 3);

int blocks[7][4][4][4] = {
    // ㄴ
    0,0,0,0,0,1,0,0,0,1,1,1,0,0,0,0,    0,0,0,0,0,1,1,0,0,1,0,0,0,1,0,0,    0,0,0,0,1,1,1,0,0,0,1,0,0,0,0,0,    0,0,1,0,0,0,1,0,0,1,1,0,0,0,0,0,
    // ㄴ반대
    0,0,0,0,0,0,1,0,1,1,1,0,0,0,0,0,    0,1,0,0,0,1,0,0,0,1,1,0,0,0,0,0,    0,0,0,0,0,1,1,1,0,1,0,0,0,0,0,0,    0,0,0,0,0,1,1,0,0,0,1,0,0,0,1,0,
    // ㅁ
    1,1,0,0,1,1,0,0,0,0,0,0,0,0,0,0,    1,1,0,0,1,1,0,0,0,0,0,0,0,0,0,0,    1,1,0,0,1,1,0,0,0,0,0,0,0,0,0,0,    1,1,0,0,1,1,0,0,0,0,0,0,0,0,0,0,
    // ㅡ
    0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,    0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,    0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,    0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,
    // ㅗ
    0,0,0,0,0,1,0,0,1,1,1,0,0,0,0,0,    0,0,0,0,0,1,0,0,0,1,1,0,0,1,0,0,    0,0,0,0,0,0,0,0,1,1,1,0,0,1,0,0,    0,0,0,0,0,1,0,0,1,1,0,0,0,1,0,0,
    // ㄱㄴ
    0,0,0,0,1,1,0,0,0,1,1,0,0,0,0,0,    0,1,0,0,1,1,0,0,1,0,0,0,0,0,0,0,    0,0,0,0,1,1,0,0,0,1,1,0,0,0,0,0,    0,1,0,0,1,1,0,0,1,0,0,0,0,0,0,0,
    // ㄱㄴ반대
    0,0,0,0,0,1,1,0,1,1,0,0,0,0,0,0,    0,1,0,0,0,1,1,0,0,0,1,0,0,0,0,0,    0,0,0,0,0,1,1,0,1,1,0,0,0,0,0,0,    0,1,0,0,0,1,1,0,0,0,1,0,0,0,0,0
};

int gameBoard[HEIGHT][WIDTH];
const char* figure[4] = { "  ", "■", "▦", "□" };

Tetris InitGame()
{
    //테트리스 정보 구조체 초기화
    Tetris t;
    t.level = 1;
    t.gameover = 0;
    t.score = 0;
    t.rotation = 0;
    t.absX = t.absY = 0;
    t.curX = t.curY = 0;
    t.curBlock = 0;
    t.nextBlock = 0;
    t.isBlockSpawn = false;

    //게임 보드 초기화
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            if (x == 0 || x == WIDTH - 1)
                gameBoard[y][x] = 1;
            else if (y == HEIGHT - 1)
                gameBoard[y][x] = 1;
            else
                gameBoard[y][x] = 0;
        }
    }
    
    return t;
}

void DrawBoard(Tetris& t)
{
    
    for (int y = 0; y < HEIGHT - 1; y++) {
        for (int x = 1; x < WIDTH - 1; x++) {
            Gotoxy(t.absX + x * 2, t.absY + y);
            if (gameBoard[y][x] == 1)
                printf("%s", figure[3]);
        }
    }
}

void DrawFrame(Tetris& t)
{
    for (int i = 0; i < HEIGHT; i++) {
        Gotoxy(t.absX, t.absY + i);
        printf("%s", figure[2]);
        Gotoxy(t.absX + WIDTH * 2 - 2, t.absY + i);
        printf("%s", figure[2]);
    }

    for (int i = 1; i < WIDTH; i++) {
        Gotoxy(t.absX + i * 2, t.absY + HEIGHT - 1);
        printf("%s", figure[2]);
    }
}

void DrawBlock(Tetris& t)
{
    //Gotoxy(t.absX + t.curX, t.absY + t.curY);
    for (int y = 0; y < 4; y++) {
        for (int x = 0; x < 4; x++) {
            if (blocks[t.curBlock][t.rotation][y][x] == 1) {
                Gotoxy(t.absX + (t.curX + x) * 2, t.absY + t.curY + y);
                printf("%s", figure[1]);
            }
        }
    }
}

void RemoveCurrentBlock(Tetris& t)
{
    for (int y = 0; y < 4; y++)
        for (int x = 0; x < 4; x++) {
            if (blocks[t.curBlock][t.rotation][y][x] == 1) {
                Gotoxy(t.absX + (x + t.curX) * 2, t.absY + y + t.curY);
                printf("%s", figure[0]);
                //printf("  ");
            }
        }
}

void Gotoxy(int x, int y)
{
	COORD pos = { x, y };

	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void RemoveCursor()
{
    CONSOLE_CURSOR_INFO curInfo = { 0, };
    curInfo.dwSize = 1;
	curInfo.bVisible = 0;
	GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);
}


void SpawnBlock(Tetris& t)
{
    t.curBlock = randomBlock(mt);
    t.rotation = randomRotaion(mt);
    //t.curBlock = 0;
    t.curX = WIDTH / 2 - 1;
    t.curY = 0;

    DrawBlock(t);

    /*
    Gotoxy(t.absX + t.curX, t.absY + t.curY);
    for (int y = 0; y < 4; y++) {
        for (int x = 0; x < 4; x++) {
            if (blocks[t.curBlock][t.rotation][y][x] == 1) {
                Gotoxy(t.absX + t.curX + x*2, t.absY + t.curY + y);
                printf("%s", figure[1]);
            }
        }
    }
    */
}

void MoveLeftAndRight(Tetris& t, int direction)
{
    RemoveCurrentBlock(t);

    t.curX += direction;

    if(CollisionCheck(t))
        t.curX -= direction;
    else
        Gotoxy(t.absX + t.curX, t.absY + t.curY);

    DrawBlock(t);
}

void MoveDown(Tetris& t)
{
    RemoveCurrentBlock(t);

    t.curY += 1;

    if (CollisionCheck(t)) {
        t.curY -= 1;
        BlockFix(t);
    }
    else
        Gotoxy(t.absX + t.curX, t.absY + t.curY);

    DrawBlock(t);
}

void RotationBlock(Tetris& t)
{
    RemoveCurrentBlock(t);

    t.rotation = (t.rotation + 1) % 4;

    if(CollisionCheck(t))
        t.rotation = (t.rotation == 0) ? 3 : (t.rotation -1) % 4;
}


bool CollisionCheck(Tetris& t)
{
    
    int dat = 0;

    for (int y = 0; y < 4; y++) {
        for (int x = 0; x < 4; x++) {
            if ((t.curX + x == 0) || (t.curX + x == WIDTH - 1))
                dat = 1;
            else
                dat = gameBoard[t.curY + y][t.curX + x];

            if (blocks[t.curBlock][t.rotation][y][x] == 1 && dat == 1)
                return true;
        }
    }
    
    return false;
}

void BlockFix(Tetris& t)
{
    for (int y = 0; y < 4; y++) {
        for (int x = 0; x < 4; x++) {
            if (blocks[t.curBlock][t.rotation][y][x] == 1)
                gameBoard[t.curY + y][t.curX + x] = 1;
        }
    }

    t.isBlockSpawn = false;
}