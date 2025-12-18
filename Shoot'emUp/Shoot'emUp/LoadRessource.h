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
	SDL_Texture* enemyTexture;
	SDL_Texture* entityTexture;
	SDL_Texture* bulletTexture;

	void loadAllTexture();

	LoadRessource(SDL_Renderer* rend);
	~LoadRessource();
};

