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
	//first_monster();
	reset_monster();
	wave_data();

	int game_start = 0;
	int game_end = 0;
	int game_clear = 0;
	int start_art = 0;
	int end_art = 0;
	int clear_art = 0;
	int x = 31;
	int y = 4;
	int point_x = 5;
	int point_y = 6;
	char key = 0;
	char coin_val[12];
	char wave_str[5];
	int change = 0; // 0일때 화살표
	int coin_check = 0;
	int current_wave = 0;
	total_spawned = 0;

	while (1)
	{
		while (1)
		{
			clear();

			if (game_start == 0)
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
			else if (castle_life <= 0)
			{
				clear();

				break;
			}
			else if (game_start == 1)
			{

				clear();

				outline(4, 2, "▒", "▒");
				if (change == 0)
				{
					render(point_x, point_y, "▶");
				}
				else
				{
					render(x, y, "●");
				}
				weapon_render();
				//test();
				store();
				_itoa_s(cost, coin_val, sizeof(coin_val), 10);
				_itoa_s(current_wave + 1, wave_str, sizeof(wave_str), 10);
				build_path();
				path_render();
				monster_move();
				monster_attack();
				monster_render();
				spawn_monster_wave(current_wave);
				render(5, 3, "COIN : ");
				render(12, 3, coin_val);
				render_life();
				render_key();
				render_choice();

				int alive_count = 0;

				for (int i = 0; i < MAX_MONSTER; i++)
				{
					if (monster[i].dead == 0) alive_count++;
				}

				if (total_spawned >= wave_monster_count[current_wave] && alive_count == 0)
				{
					if (current_wave < 4)
					{
						render(63, 3, wave_str);
						render(65, 3, "round clear!");
						current_wave++;
						total_spawned = 0;
						spawn_time = 0;

						flip();
						Sleep(2000);
					}
					else
					{
						game_clear = 1;
						break;
					}

				}

				flip();
				Sleep(30);

				switch (point_y)
				{
				case 6: { coin_check = 20; }
					  break;
				case 9: { coin_check = 40; }
					  break;
				case 12: { coin_check = 60; }
					   break;
				case 15: { coin_check = 80; }
					   break;

				}

				if (_kbhit())
				{
					key = _getch();

					if (key == -32 || key == 0)
					{
						key = _getch();
					}

					if (change == 0)
					{
						switch (key)
						{
						case UP: if (point_y > 6) { point_y -= 3; }
							   break;
						case DOWN: if (point_y < 15) { point_y += 3; }
								 break;
						case 'a': if (cost >= coin_check) { change = 1; }
								break;
						case 'A': if (cost >= coin_check) { change = 1; }
								break;
						default: render(0, 0, "잘못된 키 입력");
							break;
						}
					}
					else
					{
						switch (key)  // 실행창 안에서 움직일 범위 제한 > 설치 구간 지정하기
						{
						case UP: if (y > 4) { y--; }
							   break;
						case LEFT: if (x > 32) { x -= 2; }
								 break;
						case RIGHT:if (width - 12 > x) { x += 2; }
								  break;
						case DOWN: if (height - 8 > y) { y++; }
								 break;
						default: render(0, 0, "잘못된 키 입력");
							break;
						}
					}

					if (cost >= coin_check)
					{
						if (key == 'd' || key == 'D')
						{
							if (x < MAP_WIDTH && y < MAP_HEIGHT)
							{
								int choice_type = (point_y - 6) / 3;

								weapon_map[x][y] = choice_type + 1;

								int r = weapon_range[choice_type];

								for (int i = -r; i <= r; i++)
								{
									if (x + i >= 0 && x + i < MAP_WIDTH)
										attack_map[x + i][y] = 1;
									if (y + i >= 0 && y + i < MAP_HEIGHT)
										attack_map[x][y + i] = 1;
								}

								cost -= coin_check;
								change = 0;
							}
						}
					}
				}

			}

		}

		clear();
		if (game_clear == 1)
		{
			render_clear(); 
		}
		else if (castle_life <= 0)
		{
			render_end();   
		}
		flip();

		if (_kbhit())
		{
			char cha = _getch();
			if (cha == 'z' || cha == 'Z')
			{
				game_start = 0;
				castle_life = 3;
				game_clear = 0;
				start_art = 0;
				end_art = 0;
				clear_art = 0;
				current_wave = 0;
				total_spawned = 0;
				spawn_time = 0; 
				cost = 0;
				reset_monster();

				for (int i = 0; i < MAP_WIDTH; i++)
				{
					for (int j = 0; j < MAP_HEIGHT; j++)
					{
						weapon_map[i][j] = 0; 
						attack_map[i][j] = 0; 
						weapon_cooltime[i][j] = 0;
					}
				}

			}
			else if (cha == 'x' || cha == 'X')
			{
				release();
				return 0;
			}
		}
		Sleep(30);	
	}
}
// SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12); >> 나중에 색 바꾸는거 추가하기
// ex) 공격 받을 때 몬스터 색, 사용자가 무기 설치 가능한 지역에 있을 때 색