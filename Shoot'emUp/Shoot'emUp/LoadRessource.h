#pragma once
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <string>
#include <cstring>

class LoadRessource {
public:
    SDL_Renderer* renderer;

    // Color
    SDL_Color white = {255,255,255,255};
    
    // Textures of game
    SDL_Texture* backgroundLevel1;
    SDL_Texture* backgroundHome;
    SDL_Texture* playerTexture;
    SDL_Texture* bulletTexture;
    SDL_Texture* enemyTextureBomb;
    SDL_Texture* playerTextureHeart;
    SDL_Texture* texteTexture;

    // Font for write
    //TTF_Font* font; 

    LoadRessource(SDL_Renderer* rend);
    ~LoadRessource();

    void loadAllTexture();
    //void loadFont();
};

enum GameState {
    MENU,
    LEVEL1,
    LEVEL2,
    GAMEOVER,
    QUIT
};