#include <stdio.h>
#include <Windows.h>
#include <conio.h>

HANDLE screen[2];
int index = 0;
int size = sizeof(screen) / sizeof(screen[0]);

#define UP 72
#define LEFT 75
#define RIGHT 77
#define DOWN 80

void initialize()
{
	CONSOLE_CURSOR_INFO cursor;

	for (int i = 0; i <= 2; i++)
	{
		cursor.bVisible = FALSE;
		cursor.dwSize = 1;
		screen[i] = CreateConsoleScreenBuffer
		(
			GENERIC_READ | GENERIC_WRITE,
			0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL
		);

		SetConsoleCursorInfo(screen[i], &cursor);
	}
}

void flip()
{
	SetConsoleActiveScreenBuffer(screen[index]);

	index = !index;
}

void clear()
{
	COORD position = { 0, 0 };

	DWORD dword;

	CONSOLE_SCREEN_BUFFER_INFO buffer;

	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);

	GetConsoleScreenBufferInfo(console, &buffer);

	int width = buffer.srWindow.Right - buffer.srWindow.Left + 1;
	int height = buffer.srWindow.Bottom - buffer.srWindow.Top + 1;

	FillConsoleOutputCharacter(screen[index], ' ', width * height, position, &dword);

}

void release()
{
	for (int i = 0; i < size; i++)
	{
		CloseHandle(screen[i]);
	}
}

void render(int x, int y, const char* character)
{
	DWORD dword;
	COORD position = { x, y };

	SetConsoleCursorPosition(screen[index], position);
	WriteFile(screen[index], character, strlen(character), &dword, NULL);
}

void outline(int x, int y, const char* character1, const char* character2) // 실행창 테두리 만들기
{

	CONSOLE_SCREEN_BUFFER_INFO console;
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(handle, &console);

	int width = console.srWindow.Right - console.srWindow.Left - 2;
	int height = console.srWindow.Bottom - console.srWindow.Top;

	DWORD dword;
	COORD position = { x, y };

	
	for (int i = x; i < width; i++)
	{
		render(i, height - 7, character1);
	}
	for (int i = x; i < width-1; i++)
	{
		render(i+1, y, character1);
	}
	for (int i = y + 1; i < height - 6; i++)
	{
		render(x, i, character2);
		render(width, i, character2);
	}

}

int main()
{
	CONSOLE_SCREEN_BUFFER_INFO console;
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(handle, &console);

	int width = console.srWindow.Right - console.srWindow.Left - 2;
	int height = console.srWindow.Bottom - console.srWindow.Top;

	initialize();

	int x = 25;
	int y = 2;
	char key = 0;

	outline(24, 2, "_", "|");

	while (1)
	{
		flip();

		clear();

		key = _getch();

		if (key == -32 || key == 0)
		{
			key = _getch();
		}

		switch (key)
		{
		case UP: if (y > 2) { y--; }
			   break;
		case LEFT: if (x > 25) { x -= 2; }
				 break;
		case RIGHT:if (width -1 > x) { x += 2; }
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