#pragma once
#include <Windows.h>
#include <conio.h>
#include "buffer.h"

#define MAX_MONSTER 100
#define MAP_WIDTH 120
#define MAP_HEIGHT 40

int current_path = 0;
int castle_life = 3;
int monster_count = 0;  
int spawn_time = 0;
int total_spawned = 0;
int monster_health[] = { 5, 10, 10, 20 };
int monster_speed[] = { 8, 6, 3, 5 };
int monster_damage[] = { 1, 1, 1, 2 };
int wave_list[5][30]; 
int wave_monster_count[5] = { 5, 10, 10, 16, 25 };

struct Monster //이속, 체력, 위치, 생사여부 등 (색, 형태 나중에)
{
	int health;
	int speed;
	int dead; // 1이 죽음
	int x;
	int y;
	int position;
	int move_counter;
	int hit;
	int damage;
	int type;
}; 

struct Monster monster[MAX_MONSTER];

void first_monster() 
{
	for (int i = 0; i < MAX_MONSTER; i++)
	{
		if (monster[i].dead == 1) 
		{
			monster[i].x = path_x[0];
			monster[i].y = path_y[0];
			monster[i].health = 3;
			monster[i].speed = 8;
			monster[i].dead = 0;     
			monster[i].position = 0;
			monster[i].move_counter = 0;
			monster[i].hit = 0;

			break; 
		}
	}
}

void spawn_monster() 
{
	if (total_spawned >= MAX_MONSTER)
	{
		return;
	}

	spawn_time++;

	if (spawn_time >= 16) 
	{ 
		for (int i = 0; i < MAX_MONSTER; i++)
		{
			if (monster[i].dead == 1) 
			{ 
				first_monster();

				total_spawned++;
				spawn_time = 0; 
				break;
			}
		}
	}
}

void spawn_monster_wave(int wave) 
{
	if (total_spawned >= wave_monster_count[wave]) return;

	spawn_time++;
	if (spawn_time >= 15) 
	{
		for (int i = 0; i < MAX_MONSTER; i++)
		{
			if (monster[i].dead == 1)
			{

				int monster_type = wave_list[wave][total_spawned];

				monster[i].x = path_x[0];
				monster[i].y = path_y[0];
				monster[i].health = monster_health[monster_type];
				monster[i].speed = monster_speed[monster_type];
				monster[i].damage = monster_damage[monster_type];
				monster[i].dead = 0;
				monster[i].position = 0;
				monster[i].move_counter = 0;
				monster[i].hit = 0;
				monster[i].type = monster_type; 

				total_spawned++;
				spawn_time = 0;
				break;
			}
		}
	}
}

void path() 
{
	current_path = 0;

	int start_x = 30;
	int start_y = 12;

	for (int i = 0; i < 124; i++)
	{
		path_x[current_path] = start_x + i;
		path_y[current_path] = start_y;
		current_path++;
	}
} 

void monster_move() 
{
	for (int i = 0; i < MAX_MONSTER; i++) 
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
					castle_life -= monster[i].damage;
				}
			}
		}
	}
}

void monster_render() 
{
	const char* normal_render[] = { "♞", "♜", "♝", "♚" }; 
	const char* hit_render[] = { "♘", "♖", "♗", "♔" };

	for (int i = 0; i < MAX_MONSTER; i++) 
	{
		if (monster[i].dead == 0) 
		{
			int type = monster[i].type;

			if (monster[i].hit == 1)
			{
				render(monster[i].x, monster[i].y, (char *)hit_render[type]);
			}
			else
			{
				render(monster[i].x, monster[i].y, (char *)normal_render[type]);
			}
		}
	}
}

void reset_monster() 
{
	for (int i = 0; i < MAX_MONSTER; i++) {
		monster[i].dead = 1;
	}
	total_spawned = 0; 
}

void render_life()
{
	if (castle_life == 3)
	{
		render(103, 3, "LIFE : ♡ ♡ ♡ ");
	}
	else if (castle_life == 2)
	{
		render(103, 3, "LIFE : ♡ ♡  ");
	}
	else if (castle_life == 1)
	{
		render(103, 3, "LIFE : ♡  ");
	}
	else 
	{
		render(103, 3, "LIFE :  ");
	}
}

void wave_data() 
{
	for (int i = 0; i < 5; i++) // Wave 1 > 1번 5마리
	{
		wave_list[0][i] = 0;
	}

	for (int i = 0; i < 5; i++) // Wave 2 > 1번 5마리 2번 5마리 
	{
		wave_list[1][i] = 0;
	}
	for (int i = 5; i < 10; i++)
	{
		wave_list[1][i] = 1;
	}

	for (int i = 0; i < 10; i++) // Wave 3 > 3번 10마리
	{
		wave_list[2][i] = 2;
	}

	for (int i = 0; i < 5; i++) // Wave 4 > 1번 2번 3번 5마리 4번 1마리 
	{
		wave_list[3][i] = 0;
	}
	for (int i = 5; i < 10; i++)
	{
		wave_list[3][i] = 1;
	}
	for (int i = 10; i < 15; i++)
	{
		wave_list[3][i] = 2;
	}
	wave_list[3][15] = 3;

	for (int i = 0; i < 5; i++) // Wave 5 > 1번 2번 3번 5마리 4번 10마리 
	{
		wave_list[4][i] = 0;
	}
	for (int i = 5; i < 10; i++)
	{
		wave_list[4][i] = 1;
	}
	for (int i = 10; i < 15; i++)
	{
		wave_list[4][i] = 2;
	}
	for (int i = 15; i < 25; i++)
	{
		wave_list[4][i] = 3;
	}
}