#pragma once
#include <Windows.h>
#include <conio.h>
#include "buffer.h"

#define MAP_WIDTH 120
#define MAP_HEIGHT 40

int path_x[100];
int path_y[100];
int current_path = 0;

struct Monster //이속, 체력, 위치, 생사여부 등 (색, 형태 나중에)
{
	int health;
	int speed;
	int dead; // 1이 죽음
	int x;
	int y;
	int position;
};

Monster monster { 5, 2, 0, 31, 14, 0 };

void path()
{
	int start_x = 56;
	int start_y = 13;

	for (int i = 0; i < 50; i++)
	{
		path_x[current_path] = start_x + i;
		path_y[current_path] = start_y + i;
		current_path++;
	}
}

void monster_move()
{
	 //  몬스터가 지정된 path로 이동하도록 만들기
}