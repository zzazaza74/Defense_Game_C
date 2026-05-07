#pragma once
#include <Windows.h>
#include <conio.h>

#define MAP_WIDTH 120
#define MAP_HEIGHT 40

HANDLE screen[2];
int road_map[MAP_WIDTH][MAP_HEIGHT] = { 0 };

int path_x[1000];
int path_y[1000];
int path_count = 0;

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

	for (int i = x; i < width+1; i++)
	{
		render(i, height - 7, character1);
	}
	for (int i = x; i < width ; i++)
	{
		render(i + 1, y, character1);
	}
	for (int i = y + 1; i < height - 6; i++)
	{
		render(x, i-1, character2);
		render(width, i-1, character2);
		render(x + 26, i, character2);
	} 

	for (int i = x + 104; i < width - 1; i++) // 성 외곽 
	{
		render(i + 1, y + 5, character1);
		render(i + 1, y + 14, character1);
	}
	for (int i = y + 5; i < height - 12; i++)
	{
		render(x + 104, i, character2);
	}

}

void build_path() 
{
	path_count = 0;
	int p_x = 31; 
	int p_y = 12; 

	for (; p_x <= 46; p_x++) 
	{
		path_x[path_count] = p_x;
		path_y[path_count] = p_y;
		path_count++;
	}
	p_x--; 

	for (; p_y >= 6; p_y--) 
	{
		path_x[path_count] = p_x;
		path_y[path_count] = p_y;
		path_count++;
	}
	p_y++; 


	for (; p_x <= 61; p_x++) 
	{
		path_x[path_count] = p_x;
		path_y[path_count] = p_y;
		path_count++;
	}
	p_x--;

	for (; p_y <= 18; p_y++) 
	{
		path_x[path_count] = p_x;
		path_y[path_count] = p_y;
		path_count++;
	}
	p_y--;

	for (; p_x <= 76; p_x++) 
	{
		path_x[path_count] = p_x;
		path_y[path_count] = p_y;
		path_count++;
	}
	p_x--;

	for (; p_y >= 6; p_y--) 
	{
		path_x[path_count] = p_x;
		path_y[path_count] = p_y;
		path_count++;
	}
	p_y++;

	for (; p_x <= 91; p_x++) 
	{
		path_x[path_count] = p_x;
		path_y[path_count] = p_y;
		path_count++;
	}
	p_x--;

	for (; p_y <= 12; p_y++) 
	{
		path_x[path_count] = p_x;
		path_y[path_count] = p_y;
		path_count++;
	}
	p_y--;

	int final_x = p_x + 15;

	for (; p_x <= final_x; p_x++) 
	{
		path_x[path_count] = p_x;
		path_y[path_count] = p_y;
		path_count++;
	}
}

void path_render() 
{
	for (int i = 0; i < path_count; i++)
	{
		if (i < path_count - 1 && path_x[i] != path_x[i + 1])
		{

			if (path_x[i] % 2 != 0) 
			{
				render(path_x[i], path_y[i], "≡");
			}
			else
			{
				render(path_x[i], path_y[i], "□"); 
			}
		}
		else
		{
			render(path_x[i], path_y[i], "≡");
		}
	}
}

void store()
{
	coin_count++;

	if (coin_count > 10)
	{
		cost += 5;
		coin_count = 0;
	}
}

void render_start() 
{
	int start_x = 13;
	int start_y = 1;

	render(start_x, start_y + 0, "              B,,,,,                    wyBW                                            ");
	render(start_x, start_y + 1, "              ZZZZZZZZZj               ZZZZZZ                                           ");
	render(start_x, start_y + 2, "              ZZZ   5ZZZ               ZZZ                                              ");
	render(start_x, start_y + 3, "              ZZZ    ZZZ   8ZZZZZ8  ZZZZZZZE  ZZZZZZ   ZZZBZZZZ,   ZZZZZZj   zZZZZZE        ");
	render(start_x, start_y + 4, "              ZZZ    ZZZ  ZZZE ZZZZ ZZZZZZZ5 ZZZ  ZZZ  ZZZZjZZZZ  ZZZ  ZZZ8 ZZZZ BZZZ       ");
	render(start_x, start_y + 5, "              ZZZ    ZZZ  ZZZ   ZZZ   ZZZ   5ZZE  9ZZ  ZZZ   ZZZ  ZZZ       ZZZ   ZZZ       ");
	render(start_x, start_y + 6, "              ZZZ    ZZZ  ZZZZZZZZZ   ZZZ   BZZZZZZZZj ZZZ   ZZZ  5ZZZZZZ   ZZZZZZZZZ       ");
	render(start_x, start_y + 7, "              ZZZ    ZZZ  ZZZ         ZZZ   BZZZ       ZZZ   ZZZ       ZZZE ZZZ             ");
	render(start_x, start_y + 8, "              ZZZyjDZZZZ  ZZZ  5ZZZ   ZZZ   BZZZ  ZZZ, ZZZ   ZZZ BZZZ  9ZZZ ZZZW wZZZ       ");
	render(start_x, start_y + 9, "              ZZZZZZZZZ    ZZZZZZZ   WZZZ    ZZZZZZZ9  ZZZB ,ZZZ  ZZZZZZZZ   ZZZZZZZ        ");
	render(start_x, start_y + 11, "                            jZZZZZZy                                                        ");
	render(start_x, start_y + 12, "                          ZZZZEEZZZZ                                                        ");
	render(start_x, start_y + 13, "                          ZZZ    ZZZ      w            ,,    w        W                     ");
	render(start_x, start_y + 14, "                          ZZZ    zwE  wZZZZZZZ8  ZZZZZZZZZZZZZZ  ,ZZZZZZZW                  ");
	render(start_x, start_y + 15, "                          ZZZ  E   ,  ZZZ   ZZZ  ZZZw yZZZ  ZZZ  ZZZ   ZZZ                  ");
	render(start_x, start_y + 16, "                          ZZZ  ZZZZZ      jDZZZ  ZZZ  yZZZ  ZZZ  ZZZBWBZZZ                  ");
	render(start_x, start_y + 17, "                          ZZZ    ZZZ  ZZZZZZZZZ  ZZZ  DZZZ  ZZZ  ZZZZZZZ9Z                  ");
	render(start_x, start_y + 18, "                          ZZZ    ZZZ  ZZZ   ZZZ  ZZZ  DZZZ  ZZZ  ZZZ     Z                  ");
	render(start_x, start_y + 19, "                          ZZZZZZZZZZ  ZZZZZZZZZ  ZZZW 8ZZZ  ZZZ, ZZZZBZZZZ                  ");
	render(start_x, start_y + 20, "                           jZZZZz ZZ   ZZZZ ZZZ  ZZZW BZZZ  ZZw  WZZZZZj                    ");

	render(start_x + 29, start_y + 23, "==========================================");
	render(start_x + 30, start_y + 24, "    [ 'S' 키를 눌러 게임 시작하기 ]        ");
	render(start_x + 29, start_y + 25, "==========================================");
}

void render_end() 
{
	int start_x = 13;  
	int start_y = 2; 

	render(start_x, start_y + 0, "                    wZZZZZZZZZZZZ9 8ZZZZZZZZZ yZZZZZZZ  ZZZZZZZZZZZZZZZZZZZZZZ                    ");
	render(start_x, start_y + 1, "                   DZZZZZZZZZZZZZZ ZZZZZZZZZZ ZZZZZZZZEEZZZZZZZZZZZZZZZZZZZZZZ                    ");
	render(start_x, start_y + 2, "                8zZZZB         ZZZZZ      ZZZZZZ   ZZZZZ9   ZZ             ZZ                     ");
	render(start_x, start_y + 3, "                ZZZZ   ZZZZZZZZZZZZ   ZZ    ZZZZ     ZZ     ZZ5   ZZZZZZZZZZZ                     ");
	render(start_x, start_y + 4, "                ZZ   DZZZZZZZZZZZ   ZZZZZZ   BZZ            ZZ5   ZZZZZZZZZ                       ");
	render(start_x, start_y + 5, "                ZZ    ZZZ      ZZ   ZZZZZZ   ZZZ            ZZ5           9Z                      ");
	render(start_x, start_y + 6, "                ZZ   zZZZZZ   yZZ            ZZZ   ZZ  ZZ   ZZ5   ZZZZZZZZZ                       ");
	render(start_x, start_y + 7, "                ZZZZ   9ZZZ   yZZ   ZZZZZZ   ZZZ   ZZZZZZ   ZZ5   ZZZZZZZZZZZ                     ");
	render(start_x, start_y + 8, "                  ZZZZ         ZZ   jZZZZZ   zZZ   ZZZZZD   ZZ             ZZ                     ");
	render(start_x, start_y + 9, "                  ZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZ                    ");
	render(start_x, start_y + 10, "                  ZZZZZZZZZZZZ  ZZZZZZZZZZZZZZ yZZZZZZZZZZZZE zZZZZZZZZZZZZ,D                    ");
	render(start_x, start_y + 11, "                ZZZZ         ZZZZ   yZZZZZ   ZZZ            ZZD           ZZZZ                    ");
	render(start_x, start_y + 12, "                ZZ   jZZZZZ   WZZ   9ZZZZZ   ZZZ   ZZZZZZZZZZZy   ZZZZZD   ZZ                    ");
	render(start_x, start_y + 13, "                ZZ   ,ZZZZZ   WZZ   ZZZZZZ   ZZZ   ZZZZZZZZZZZ5   ZZZZZE   ZZ                    ");
	render(start_x, start_y + 14, "                ZZ    ZZZZZ   yZZ     ZZ     zZZ          wZZZ5   ZZZZ     ZZ                    ");
	render(start_x, start_y + 15, "                ZZ    ZZZZZ   yZZE8     y    ZZZZ   ZZ99EEBZZZZ5        ZZZ9ZZ                    ");
	render(start_x, start_y + 16, "                ZZ   yZZZZZ    ZZZZZ      ZZZZZZ   ZZZZZZZZZZZ5   Zy   BBZZZZ                    ");
	render(start_x, start_y + 17, "                ZZzE       ,  ZZZZjZZZZ  ZEZZjZZZ            ZZ,   ZZ85     ZZ                    ");
	render(start_x, start_y + 18, "                ZZZZW5w,wwj5DZZZZ ZZZZ8,ZZZZ zZZw8Bywwwww,, ZZZyzWZZZZy8Bj ZZ                    ");
	render(start_x, start_y + 19, "                  ZZZZZZZZZZZZZ      ZZZZZZ   ZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZ                    ");

	render(start_x + 30, start_y + 22, "[ 'Z' : 다시하기 / 'X' : 나가기 ]");
}

void render_key()
{
	render(5, 19, " 방향키로 이동");
	render(5, 20, " 'A' 키로 무기 선택");
	render(5, 21, " 'D' 키로 무기 설치");
}
void render_choice()
{
	render(6, 6, "【눈덩이 】 ¨ 20코인 ¨ ");
	render(6, 7, "데미지 1:범위 2:공속 5 ");
	render(6, 9, "【죽창 】 ¨ 40코인 ¨ ");
	render(6, 10, "데미지 3:범위 2:공속 5 ");
	render(6, 12, "【화살 】 ¨ 60코인 ¨ ");
	render(6, 13, "데미지 2:범위 3:공속 10 ");
	render(6, 15, "【대포 】 ¨ 80코인 ¨ ");
	render(6, 16, "데미지 4:범위 3:공속 8 ");

}


