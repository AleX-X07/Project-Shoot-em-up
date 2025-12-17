#pragma once
#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <iostream>
#include <cstring>
#include "LoadRessource.h"

class Menu {
public:

	int menuSelection;
	bool upPressed;
	bool downPressed;
	bool enterPressed;

	//SDL_Color color;
	SDL_Texture* background;
	SDL_Texture* titleTexture;
	SDL_Texture* playTexture;
	SDL_Texture* quitTexture;

	Menu(SDL_Texture* background);
	//Menu(SDL_Color color);
	~Menu();
	void loadMenuTextures(LoadRessource& resources);
	static void ButtonMenu(SDL_Renderer* renderer, int w, int h, SDL_Color color, const char* text, TTF_Font* font, int x2, int y2, int w2, int h2, int menuSelection, int Selection);
	static void TitleMenu(SDL_Renderer* renderer, int w, int h, SDL_Color color, const char* text, TTF_Font* font, int x2, int y2, int w2, int h2);
	GameState DisplayMenu(SDL_Renderer* renderer, SDL_Window* window, TTF_Font* font, LoadRessource MyRessources);
};



