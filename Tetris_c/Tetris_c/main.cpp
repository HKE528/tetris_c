#include "Tetris.h"

int main()
{
	Tetris t = InitGame();
	bool isBlockSpawn = false;

	char key;

	while (1) {
		system("cls");
		DrawBoard(t);
		DrawBlock(t);
		RemoveCursor();

		if (!isBlockSpawn) {
			SpawnBlock(t);
			isBlockSpawn = true;
		}

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