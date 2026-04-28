#include <stdio.h>
#include <Windows.h>
#include <conio.h>
#include "buffer.h"

#define UP 72
#define LEFT 75
#define RIGHT 77
#define DOWN 80
#define MAP_WIDTH 120
#define MAP_HEIGHT 40


int main()
{
	CONSOLE_SCREEN_BUFFER_INFO console;
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(handle, &console);

	int width = console.srWindow.Right - console.srWindow.Left - 2;
	int height = console.srWindow.Bottom - console.srWindow.Top;

	initialize();

	int x = 31;
	int y = 4;
	char key = 0;

	while (1)
	{
		clear();

		outline(4, 2, "_", "|");
		render(x, y, "※");
		weapon_render();
		test();

		flip();

		if (_kbhit())
		{
			key = _getch();

			if (key == -32 || key == 0)
			{
				key = _getch();
			}

			switch (key)  // 실행창 안에서 움직일 범위 제한
			{
			case UP: if (y > 4) { y--; }
				   break;
			case LEFT: if (x > 32) { x -= 2; }
					 break;
			case RIGHT:if (width - 12 > x) { x += 2; }
					  break;
			case DOWN: if (height - 8 > y) { y++; }
					 break;
			default: render(0, 0, "xxxxxxxx\n");
				break;
			}

			if (key == 'd')
			{
				if (x < MAP_WIDTH && y < MAP_HEIGHT)
				{
					weapon_map[x][y] = 1;

					attack_map[x+1][y] = 1;
					attack_map[x-1][y] = 1;
					attack_map[x][y+1] = 1;
					attack_map[x][y-1] = 1;
				}
			}
		}
	}
	release();

	return 0;
}
// SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12); >> 나중에 색 바꾸는거 추가하기
// ex) 공격 받을 때 몬스터 색, 사용자가 무기 설치 가능한 지역에 있을 때 색