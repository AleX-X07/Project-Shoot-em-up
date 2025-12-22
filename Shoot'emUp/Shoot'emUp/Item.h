#pragma once
// Librairie externe
#include <vector>
#include <iostream>

// Load SDL
#include <SDL3/SDL.h>

// Load file
#include "Hero.h"
#include "Enemy.h"

// Class Item, for Heart that heal player
class Item
{

public:

	// Variable for position/dimension
	SDL_FRect rect;
	float x, y;
	float w, h;

	// Vector for item
	std::vector<Item> itemVector;

	// Variable for his characteristic
	SDL_Texture* itemTexture;
	float speed;

	// Variable for time spawn
	Uint32 lastSpawnTime = 0;
	Uint32 now = SDL_GetTicks();

	// Constructor
	Item();

	// Render/Update
	static void renderItem(SDL_Renderer* renderer, std::vector<Item>& item);
	static void updateItem(std::vector<Item>& item, float dt);

	// Check collision with player
	static void collidePlayer(std::vector<Item>& item, Hero& player);

	// Spawn item
	static void itemSpawn(std::vector<Item>& item, SDL_Texture* itemTexture, int windowWidth, int windowHeight);
};

