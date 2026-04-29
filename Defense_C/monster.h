#pragma once
#include <Windows.h>
#include <conio.h>
#include "buffer.h"


#define MAP_WIDTH 120
#define MAP_HEIGHT 40

int path_x[150];
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
	int move_counter;
};

struct Monster monster = { 5, 10, 0, 32, 11, 0 , 0};

void path() // 나중에 복잡하게 바꾸기
{
	int start_x = 32;
	int start_y = 11;

	for (int i = 0; i < 50; i++)
	{
		path_x[current_path] = start_x + i;
		path_y[current_path] = start_y;
		current_path++;
	}
} 

void monster_move() // 길 바뀌고 나면 동선 수정하기
{
	if (monster.dead == 1)
	{
		return;
	}

	monster.move_counter++;

	if (monster.move_counter < monster.speed)
	{
		return;
	}

	monster.move_counter = 0;

	if (monster.position < current_path)
	{
		monster.x = path_x[monster.position];
		monster.y = path_y[monster.position];
		monster.position++;
	}
	else
	{
		monster.dead = 1;
	}
} 

extern struct Monster monster;