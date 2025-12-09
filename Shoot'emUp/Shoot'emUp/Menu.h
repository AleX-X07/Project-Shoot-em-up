#pragma once
#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>

void ButtonMenu(SDL_Renderer* renderer, int w, int h, SDL_Color color, const char* text, TTF_Font* font, int x2, int y2, int w2, int h2, int menuSelection, int Selection);
void TitleMenu(SDL_Renderer* renderer, int w, int h, SDL_Color color, const char* text, TTF_Font* font, int x2, int y2, int w2, int h2);
