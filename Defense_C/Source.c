#include <stdio.h>
#include <Windows.h>
#include <conio.h>
#include "buffer.h"

#define UP 72
#define LEFT 75
#define RIGHT 77
#define DOWN 80


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

	outline(4, 2, "_", "|"); 

	while (1)
	{
		flip();

		//clear();

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

		render(x, y, "※");
		// if (_kbhit()) // 뭔지 찾아볼것
		// {
		// 	
		// }
	}
	release();

	return 0;
}