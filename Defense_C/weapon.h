#pragma once
#include <Windows.h>
#include <conio.h>
#include "monster.h"
#include "buffer.h"

#define MAP_WIDTH 120
#define MAP_HEIGHT 40

int weapon_map[MAP_WIDTH][MAP_HEIGHT] = { 0 };
int attack_map[MAP_WIDTH][MAP_HEIGHT] = { 0 };

struct Weapon 
{
	int speed;
	int attack_counter;
	int damage; 
};

struct Weapon weapon = { 7, 0, 0 };

void weapon_render() // 길 위에는 설치 안되게 막기
{
	for (int i = 0; i < MAP_WIDTH; i++)
	{
		for (int j = 0; j < MAP_HEIGHT; j++)
		{
			if (weapon_map[i][j] == 1)
			{
				render(i, j, "d");
			}
		}
	}
}

void test() // 공격 범위 잘 지정 되는지 테스트
{
	for (int i = 0; i < MAP_WIDTH; i++)
	{
		for (int j = 0; j < MAP_HEIGHT; j++)
		{
			if (attack_map[i][j] == 1)
			{
				if (weapon_map[i][j] != 1)
				{
					render(i, j, "a");
				}

			}
		}
	}
}

void monster_attack()
{
	weapon.attack_counter++;

	if (weapon.attack_counter < weapon.speed)
	{
		return;
	}

	weapon.attack_counter = 0;

	for (int i = 0; i < FIRST_WAVE; i++)
	{
		if (monster[i].dead == 0)
		{
			if (attack_map[monster[i].x][monster[i].y] == 1)
			{
				monster[i].hit = 1;

				if (monster[i].health > 1)
				{
					monster[i].health--;
				}
				else
				{
					monster[i].dead = 1;
				}
			}
			else
			{
				monster[i].hit = 0;
			}
		}
	}
}
