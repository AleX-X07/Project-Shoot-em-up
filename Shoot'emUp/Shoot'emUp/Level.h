#pragma once
#include "Hero.h"
#include "LoadRessource.h"

class Enemy;

struct Level
{
	int nbr_enemy;
	int nbr_shooter;
	int nbr_shooter_V2;
	int nbr_boss;
	bool levelWithBoss;

	int nbr_enemy_total;
	int nbr_shooter_total;
	int nbr_shooter_V2_total;
	int nbr_boss_total;

	float spawnTimer = 0;
	float spawnInterval = 1;

	int numLevel;
	
	Level();
	void setMyLevel(int _nbr_enemy, int _nbr_shooter, int _nbr_shooter_V2, int _nbr_boss);
	int typeLevel(Entity& player);
	void displayLevel(SDL_Renderer* renderer, LoadRessource& MyRessource, Entity& player, float dt, SDL_Window* window, std::vector<Enemy>& enemies, std::vector<Bullet>& bullets, Level& MyLevel, const bool* keys, int w, int h);
	void reset(Entity& player, std::vector<Enemy>& enemies);

};

