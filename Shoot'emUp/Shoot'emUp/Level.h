#pragma once
// Load file
#include "Hero.h"
#include "LoadRessource.h"
#include "FileManager.h"

// Foward declaration for Enemy and Item
class Enemy;
class Item;

// Class Level for level
class Level
{
public:

	// Variable for enemies number
	int nbr_enemy;
	int nbr_shooter;
	int nbr_shooter_V2;
	int nbr_boss;
	bool levelWithBoss;

	// Variable for save enemies number total
	int nbr_enemy_total;
	int nbr_shooter_total;
	int nbr_shooter_V2_total;
	int nbr_boss_total;

	// Variable for enemies spawn interval
	float spawnTimer = 0;
	float spawnInterval = 0.50;

	float spawnTimerItem = 0;
	float spawnIntervalItem = 10;

	// Variable for know the current level
	int numLevel;

	// Constructor
	Level();

	// Function for set level
	void setMyLevel(int _nbr_enemy, int _nbr_shooter, int _nbr_shooter_V2, int _nbr_boss);

	// Function for the winCondition
	int typeLevel(Hero& player);

	// Function for display level
	void displayLevel(SDL_Renderer* renderer, LoadRessource& MyRessource, Hero& player, float dt, SDL_Window* window, std::vector<Enemy>& enemies, std::vector<Bullet>& bullets, Level& MyLevel, const bool* keys, int w, int h, std::vector<Item>& item);
	
	// Function for reset player between 2 level
	void reset(Hero& player, std::vector<Enemy>& enemies);

	// Function for restart à party
	void restart(Hero& player, Enemy& MyEnemy, Item& MyItem, Level& MyLevel, bool& restart);

};

