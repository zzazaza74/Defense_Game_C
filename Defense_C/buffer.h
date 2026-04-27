#pragma once
#include <Windows.h>
#include <conio.h>

HANDLE screen[2];

int index = 0;
int size = sizeof(screen) / sizeof(screen[0]);

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

void clear()  // >> 사용자 커서만 사라지게 하기와 몬스터들 이동할때 사라지게 하는거 추가(이속 따라 달라야함)
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

	for (int i = x + 104; i < width - 1; i++) // 성 외곽 > 나중에 모양 바꾸기
	{
		render(i + 1, y + 5, character1);
		render(i + 1, y + 13, character1);
	}
	for (int i = y + 6; i < height - 13; i++)
	{
		render(x + 104, i, character2);
	}

	for (int i = x + 25; i < width - 11; i++) // 길 외곽 > 라인 정하기
	{
		render(i + 1, y + 8, character1);
		render(i + 1, y + 10, character1);
	}
	for (int i = y + 6; i < height - 13; i++)
	{
		render(x + 104, i, character2);
	}
}

void monster_movement_path() // 몬스터 이동 경로 지정(시작 위치 2개로) >> 이거 몬스터 설정에 병합하기
{

}

void monster_setting() 
{
	// 몹 설정 (이속, 체력, 공격력, 색, 형태 등) / 매개 변수는 몹 종류, 소환 수, (소환 위치) 


}

