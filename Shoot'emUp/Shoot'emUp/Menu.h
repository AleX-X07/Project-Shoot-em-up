#pragma once
// Load SDL
#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>

// Function for write on screen
void Texte(SDL_Renderer* renderer, int w, int h, SDL_Color color, const char* text, TTF_Font* font, int x2, int y2, int w2, int h2);

// Function for display button
void Button(SDL_Renderer* renderer, int w, int h, SDL_Color color, const char* text, TTF_Font* font, float x2, float y2, float w2, float h2, int menuSelection, int Selection);


