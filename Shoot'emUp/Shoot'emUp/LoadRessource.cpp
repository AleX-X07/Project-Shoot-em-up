#include "LoadRessource.h"

LoadRessource::LoadRessource(SDL_Renderer* rend) : renderer(rend) { // Initialise all texture
    backgroundLevel1 = nullptr;
    backgroundHome = nullptr;
    playerTexture = nullptr;
    bulletTexture = nullptr;
    enemyTextureBomb = nullptr;
    playerTextureHeart = nullptr;
    font = nullptr;
    texteTexture = nullptr;
}

LoadRessource::~LoadRessource() { // Destroy all texture
    if (backgroundLevel1) SDL_DestroyTexture(backgroundLevel1);
    if (backgroundHome) SDL_DestroyTexture(backgroundHome);
    if (playerTexture) SDL_DestroyTexture(playerTexture);
    if (bulletTexture) SDL_DestroyTexture(bulletTexture);
    if (enemyTextureBomb) SDL_DestroyTexture(enemyTextureBomb);
    if (playerTextureHeart) SDL_DestroyTexture(playerTextureHeart);
    if (font) TTF_CloseFont(font);
    if (texteTexture) SDL_DestroyTexture(texteTexture);
}

void LoadRessource::loadAllTexture() { // Load Texture
    SDL_Surface* surface;

    // Background
    surface = IMG_Load("picture/level-1.png");
    backgroundLevel1 = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_DestroySurface(surface);

    // Background Home
    surface = IMG_Load("picture/homeScreen.png");
    backgroundHome = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_DestroySurface(surface);
    SDL_SetTextureScaleMode(backgroundHome, SDL_SCALEMODE_NEAREST);

    // Player
    surface = IMG_Load("picture/player.png");
    playerTexture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_DestroySurface(surface);

    // Bullet
    surface = IMG_Load("picture/bullet.png");
    bulletTexture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_DestroySurface(surface);

    // Enemy
    surface = IMG_Load("picture/bomb.png");
    enemyTextureBomb = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_DestroySurface(surface);
    SDL_SetTextureScaleMode(enemyTextureBomb, SDL_SCALEMODE_NEAREST);

    //HeartPLayer
    surface = IMG_Load("picture/heart.png");
    playerTextureHeart = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_DestroySurface(surface);
    SDL_SetTextureScaleMode(playerTextureHeart, SDL_SCALEMODE_NEAREST);
}

void LoadRessource::loadFont() { // Load font for write
    font = TTF_OpenFont("assets/arialmt.ttf", 32);
    if (!font) {
        SDL_Log("Erreur chargement police: %s", SDL_GetError());
    }
}

SDL_Texture* LoadRessource::createTextTexture(const char* text, SDL_Color color, int *h, int *w) {
    if (!font) {
        SDL_Log("ERREUR: Police non chargée!");
        return nullptr;
    }

    SDL_Surface* texteSurface = TTF_RenderText_Blended(font, text, 0, color);
    if (!texteSurface) {
        SDL_Log("Erreur création surface texte: %s", SDL_GetError());
        return nullptr;
    }

    *w = texteSurface->w;
    *h = texteSurface->h;

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, texteSurface);
    SDL_DestroySurface(texteSurface);

    if (!texture) {
        SDL_Log("Erreur création texture texte: %s", SDL_GetError());
        return nullptr;
    }

    return texture;
}