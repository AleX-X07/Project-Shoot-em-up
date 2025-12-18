#pragma once
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_ttf/SDL_ttf.h>

class LoadRessource
{
public:
	//Surfce
	SDL_Renderer* renderer;

	//Texture
	SDL_Texture* backgroundHome;
	SDL_Texture* backgroundLevel1;
	SDL_Texture* heart;
	SDL_Texture* bomb;
	SDL_Texture* entityTexture;
	SDL_Texture* bulletTexture;
	SDL_Texture* ship;
	SDL_Texture* bulletEnemyTexture;

	void loadAllTexture();

	LoadRessource(SDL_Renderer* rend);
	~LoadRessource();
};

