#pragma once
#include <SDL3/SDL.h>
#include <vector>
#include <iostream>
#include "Hero.h"
#include "Enemy.h"

class Item
{
	SDL_FRect rect;
	SDL_Texture* itemTexture;
	SDL_Color color;


	Uint32 lastSpawnTime = 0;
	Uint32 now = SDL_GetTicks();

	float x, y;
	float w, h;
	float speed;

public:

	std::vector<Item> itemVector;

	Item();
	static void renderItem(SDL_Renderer* renderer, std::vector<Item>& item);
	static void updateItem(std::vector<Item>& item, float dt);
	static void collidePlayer(std::vector<Item>& item, Entity& player);
	static void itemSpawn(std::vector<Item>& item, SDL_Texture* itemTexture, int windowWidth, int windowHeight);
};

