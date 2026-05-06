#include <stdio.h>
#include <Windows.h>
#include <conio.h>
#include "buffer.h"
#include "monster.h"
#include "weapon.h"

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
	path();
	first_monster();
	reset_monsters();

	int game_start = 0;
	int game_end = 0;
	int start_art = 0;
	int end_art = 0;
	int x = 31;
	int y = 4;
	char key = 0;
	char coin_val[12];
	total_spawned = 0;
	
	while (1)
	{
		while (1)
		{
			clear();

			if (game_start == 0  )
			{

				if (start_art == 0) 
				{ 
					render_start();     
					flip();
					start_art = 1;  
				}

				if (_kbhit())
				{
					char ch = _getch();
					if (ch == 's' || ch == 'S')
					{
						game_start = 1;
					}
				}
				Sleep(30);
			}
			else if (castle_life == 0 )
			{
				clear();

				break;
			}
			else if (game_start == 1)
			{

				clear();

				outline(4, 2, "▒", "▒");
				render(x, y, "●");
				weapon_render();
				test();
				store();
				_itoa_s(cost, coin_val, sizeof(coin_val), 10);
				build_path();
				path_render();
				spawn_monster();
				monster_move();
				monster_attack();
				monster_render();
				render(5, 3, "COIN : ");
				render(12, 3, coin_val);
				render_life();
				render_key();
				render_choice();

				flip();
				Sleep(30);

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

					if (cost >= 20)
					{
						if (key == 'd')
						{
							if (x < MAP_WIDTH && y < MAP_HEIGHT)
							{
								weapon_map[x][y] = 1;

								if (x - 1 >= 0) attack_map[x - 1][y] = 1;
								attack_map[x][y] = 1;
								if (x + 1 < MAP_WIDTH) attack_map[x + 1][y] = 1;

								if (x - 3 >= 0) attack_map[x - 3][y] = 1;
								if (x + 3 < MAP_WIDTH) attack_map[x + 3][y] = 1;

								for (int j = -2; j <= 2; j++)
								{
									if (y + j >= 0 && y + j < MAP_HEIGHT)
										attack_map[x][y + j] = 1;
								}

								cost -= 20;
							}
						}
					}

				}
			}

		}

		if (end_art == 0)
		{
			render_end();
			flip();
			end_art = 1;
		}

		if (_kbhit())
		{
			char cha = _getch();
			if (cha == 'z' || cha == 'Z')
			{
				game_start = 0;
			}
			else if (cha == 'x' || cha == 'X')
			{
				break;
			}
		}
		Sleep(30);
	}
	release();

	return 0;
}
// SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12); >> 나중에 색 바꾸는거 추가하기
// ex) 공격 받을 때 몬스터 색, 사용자가 무기 설치 가능한 지역에 있을 때 색