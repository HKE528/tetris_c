#include "Tetris.h"

int main()
{
	Tetris t = InitGame();
	bool isBlockSpawn = false;

	char key;

	RemoveCursor();

	while (1) {
		system("cls");
		DrawBoard(t);
		DrawBlock(t);
		
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
				if(!CollisionCheck(t))
					MoveDown(t);
				break;

			case LEFT:
				if (!CollisionCheck(t))
					MoveLeftAndRight(t, -1);
				break;

			case RIGHT:
				if (!CollisionCheck(t))
					MoveLeftAndRight(t, 1);
				break;
			}
			if (key == SPACE) {
				printf("SPACE\n");
			}
		}
	}
} 