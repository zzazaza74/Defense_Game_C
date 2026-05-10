#pragma once
#include <Windows.h>
#include <conio.h>
#include "monster.h"
#include "buffer.h"

#define MAP_WIDTH 120
#define MAP_HEIGHT 40

int weapon_map[MAP_WIDTH][MAP_HEIGHT] = { 0 };
int attack_map[MAP_WIDTH][MAP_HEIGHT] = { 0 };

int weapon_speed[] = { 8, 8, 4, 5 };
int weapon_damage[] = { 1, 3, 2, 4 };
int weapon_range[] = { 2, 2, 3, 3 };
int weapon_cooltime[MAP_WIDTH][MAP_HEIGHT] = { 0 };
const char* weapon_shape[] = { "○", "♧", "♤", "☆" };

struct Weapon 
{
	int speed;
	int attack_counter;
	int damage; 
	int range;
};

struct Weapon weapon = { 7, 0, 1, 2 };

struct Weapon weapon_snow = { 4, 0, 1, 2};
struct Weapon weapon_spear = { 4, 0, 3, 2 };
struct Weapon weapon_arrow = { 2, 0, 2, 3 };
struct Weapon weapon_cannon = { 3, 0, 4, 3 };

void weapon_render() // 길 위에는 설치 안되게 막기
{
	for (int i = 0; i < MAP_WIDTH; i++)
	{
		for (int j = 0; j < MAP_HEIGHT; j++)
		{
			if (weapon_map[i][j] > 0)
			{
				int type = weapon_map[i][j] - 1; 
				render(i, j, (char*)weapon_shape[type]);
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
    for (int i = 0; i < MAX_MONSTER; i++)
    {
        if (monster[i].dead == 1) continue;

        monster[i].hit = 0;

        for (int j = -3; j <= 3; j++)
        {
            if (monster[i].dead == 1) break;

            for (int k = -3; k <= 3; k++)
            {
                if (j != 0 && k != 0) continue;

                int a = monster[i].x + j;
                int b = monster[i].y + k;

                if (a >= 0 && a < MAP_WIDTH && b >= 0 && b < MAP_HEIGHT)
                {
                    if (weapon_map[a][b] > 0)
                    {
                        int type = weapon_map[a][b] - 1;
                        int range = weapon_range[type];

                        if (abs(j) <= range && abs(k) <= range)
                        {
                            weapon_cooltime[a][b]++;

                            if (weapon_cooltime[a][b] >= weapon_speed[type])
                            {
                                monster[i].hit = 1;
                                monster[i].health -= weapon_damage[type];
                                weapon_cooltime[a][b] = 0;
                            }

                            if (monster[i].health <= 0)
                            {
                                monster[i].dead = 1;
                                cost += 10;
                                break;
                            }
                        }
                    }
                }
            }
        }
    }
}