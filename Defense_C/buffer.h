#pragma once
#include <Windows.h>
#include <conio.h>

#define MAP_WIDTH 120
#define MAP_HEIGHT 40

HANDLE screen[2];

int index = 0;
int size = sizeof(screen) / sizeof(screen[0]);
int cost = 0;
int coin_count = 0;

void initialize()
{
	CONSOLE_CURSOR_INFO cursor;

	for (int i = 0; i < 2; i++)
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

	GetConsoleScreenBufferInfo(screen[index], &buffer);

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

void outline(int x, int y, const char* character1, const char* character2) // 실행창 테두리 만들기 >> 가로 세로 같은 기호로 바꾸기
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
	for (int i = x; i < width - 1; i++)
	{
		render(i + 1, y, character1);
	}
	for (int i = y + 1; i < height - 6; i++)
	{
		render(x, i, character2);
		render(width, i, character2);
		render(x + 24, i, character2);
	} 

	for (int i = x + 104; i < width - 1; i++) // 성 외곽 
	{
		render(i + 1, y + 5, character1);
		render(i + 1, y + 13, character1);
	}
	for (int i = y + 6; i < height - 13; i++)
	{
		render(x + 104, i, character2);
	}

	for (int i = x + 25; i < width - 11; i++) // 길 외곽 
	{
		render(i + 1, y + 8, character1);
		render(i + 1, y + 10, character1);
	}
	for (int i = y + 6; i < height - 13; i++)
	{
		render(x + 104, i, character2);
	}
}

void store()
{
	coin_count++;

	if (coin_count < 50)
	{
		cost++;
		coin_count = 0;
	}
}
