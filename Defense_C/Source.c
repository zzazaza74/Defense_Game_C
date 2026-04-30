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

	int x = 31;
	int y = 4;
	char key = 0;
	char coin_val[12];
	

	while (1)
	{
		clear();

		outline(4, 2, "_", "|");
		render(x, y, "※");
		weapon_render();
		test();
		monster_move();
		monster_attack();
		store();
		_itoa_s(cost, coin_val, sizeof(coin_val), 10);
		spawn_monster();   
		monster_move();          
		monster_render();  

		render(5, 3, "COIN : "); 
		render(12, 3, coin_val);

		// if (monster.dead == 0)
		// {
		// 	if (weapon.damage == 1)
		// 	{
		// 		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4); //색은 나중에
		// 		render(monster.x, monster.y, "m"); // 데미지를 받으면 소문자로 변함
		// 	}
		// 	else
		// 	{
		// 		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
		// 		render(monster.x, monster.y, "M");
		// 	}
		// }
		
		if (castle_life == 0)
		{
			render(5, 4, "Game Over");
		}

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

			if (cost > 20)
			{
				if (key == 'd')
				{
					if (x < MAP_WIDTH && y < MAP_HEIGHT)
					{
						weapon_map[x][y] = 1;

						attack_map[x + 1][y] = 1;
						attack_map[x - 1][y] = 1;
						attack_map[x + 2][y] = 1;
						attack_map[x - 2][y] = 1;
						attack_map[x][y + 1] = 1;
						attack_map[x][y - 1] = 1;
						attack_map[x][y + 2] = 1;
						attack_map[x][y - 2] = 1;

						cost -= 20;
					}
				}
			}
			
		}

	}
	release();

	return 0;
}
// SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12); >> 나중에 색 바꾸는거 추가하기
// ex) 공격 받을 때 몬스터 색, 사용자가 무기 설치 가능한 지역에 있을 때 색