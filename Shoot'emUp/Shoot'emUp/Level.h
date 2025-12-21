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
	int nbr_enemy_death;
	bool levelWithBoss;

	float spawnTimer = 0;
	float spawnInterval = 1;
	
	Level();
	void setMyLevel(int _nbr_enemy, int _nbr_shooter, int _nbr_shooter_V2, int _nbr_boss, int _nbr_enemy_death);
	int typeLevel(Entity& player);
	void displayLevel(SDL_Renderer* renderer, LoadRessource& MyRessource, Entity& player, float dt, SDL_Window* window, std::vector<Enemy>& enemies, std::vector<Bullet>& bullets, bool& restart, Level& MyLevel, const bool* keys, int w, int h);

};

