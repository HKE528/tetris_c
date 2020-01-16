#include "Tetris.h"

int main()
{
	Tetris t = InitGame();
	char key;

	RemoveCursor();
	DrawFrame(t);


	while (1) {
		//system("cls");
		if (!t.isBlockSpawn) {
			SpawnBlock(t);
			t.isBlockSpawn = true;
		}

		MoveDown(t);
		DrawBoard(t);
		Sleep(100);

		while (_kbhit()) {
			key = _getch();
			switch (key) {
			case UP:
				RotationBlock(t);
				break;

			case DOWN:
				MoveDown(t);
				break;

			case LEFT:
				MoveLeftAndRight(t, -1);
				break;

			case RIGHT:
				MoveLeftAndRight(t, 1);
				break;
			}
			if (key == SPACE) {
				printf("SPACE\n");
			}
		}
	}
} 