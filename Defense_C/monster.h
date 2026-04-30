#pragma once
#include <Windows.h>
#include <conio.h>
#include "buffer.h"

#define FIRST_WAVE 5
#define MAP_WIDTH 120
#define MAP_HEIGHT 40

int path_x[100];
int path_y[100];
int current_path = 0;
int castle_life = 3;
int monster_count = 0;  
int spawn_time = 0;

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

// struct Monster monster = { 5, 10, 0, 32, 12, 0 , 0}; 
struct Monster monster[FIRST_WAVE];

void first_monster()
{
	for (int i = 0; i < FIRST_WAVE; i++)
	{
		monster[i].health = 3;
		monster[i].speed = 10;
		monster[i].dead = 0;
		monster[i].position = 0;
		monster[i].move_counter = 0;
	}
}

void spawn_monster() 
{
	spawn_time++;

	if (spawn_time >= 20) 
	{
		for (int i = 0; i < FIRST_WAVE; i++) 
		{
			if (monster[i].dead == 1) 
			{ 
				monster[i].dead = 0;
				monster[i].health = 5;
				monster[i].position = 0;
				monster[i].x = path_x[0];
				monster[i].y = path_y[0];

				spawn_time = 0; 
				break; 
			}
		}
	}
}

void path() // 나중에 복잡하게 바꾸기
{
	int start_x = 32;
	int start_y = 12;

	for (int i = 0; i < 73; i++)
	{
		path_x[current_path] = start_x + i;
		path_y[current_path] = start_y;
		current_path++;
	}
} 

// void monster_move() // 길 바뀌고 나면 동선 수정하기
// {
// 	if (monster.dead == 1)
// 	{
// 		return;
// 	}
// 
// 	monster.move_counter++;
// 
// 	if (monster.move_counter < monster.speed)
// 	{
// 		return;
// 	}
// 
// 	monster.move_counter = 0;
// 
// 	if (monster.position < current_path)
// 	{
// 		monster.x = path_x[monster.position];
// 		monster.y = path_y[monster.position];
// 		monster.position++;
// 	}
// 	else
// 	{
// 		monster.dead = 1;
// 		castle_life--;
// 	}
// } 

void monster_move() {
	for (int i = 0; i < FIRST_WAVE; i++) 
	{
		if (monster[i].dead == 0) 
		{
			monster[i].move_counter++;
			if (monster[i].move_counter >= monster[i].speed) 
			{
				monster[i].move_counter = 0;

				if (monster[i].position < current_path - 1) 
				{
					monster[i].position++;
					monster[i].x = path_x[monster[i].position];
					monster[i].y = path_y[monster[i].position];
				}
				else 
				{
					monster[i].dead = 1; 
				}
			}
		}
	}
}

void monster_render() {
	for (int i = 0; i < FIRST_WAVE; i++) 
	{
		if (monster[i].dead == 0) 
		{
			render(monster[i].x, monster[i].y, "M");
		}
	}
}
