#include "LoadRessource.h"



LoadRessource::LoadRessource(SDL_Renderer* rend) : renderer(rend) {
	backgroundHome = nullptr;
	backgroundLevel1 = nullptr;
	heart = nullptr;
    bomb = nullptr;
	entityTexture = nullptr;
	bulletTexture = nullptr;
    ship = nullptr;
    bulletEnemyTexture = nullptr;
}

void LoadRessource::loadAllTexture() {
    SDL_Surface* surface;

    // Background Home
    surface = IMG_Load("picture/home.png");
    backgroundHome = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_DestroySurface(surface);
    SDL_SetTextureScaleMode(backgroundHome, SDL_SCALEMODE_NEAREST);

    // Background Level 1
    surface = IMG_Load("picture/level1.png");
    backgroundLevel1 = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_DestroySurface(surface);

    // Heart
    surface = IMG_Load("picture/heart.png");
    heart = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_DestroySurface(surface);

    // Bomb
    surface = IMG_Load("picture/bomb.png");
    bomb = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_DestroySurface(surface);
    SDL_SetTextureScaleMode(bomb, SDL_SCALEMODE_NEAREST);

    // Player
    surface = IMG_Load("picture/player.png");
    entityTexture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_DestroySurface(surface);
    SDL_SetTextureScaleMode(entityTexture, SDL_SCALEMODE_NEAREST);

    // Bullet
    surface = IMG_Load("picture/bullet.png");
    bulletTexture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_DestroySurface(surface);

    // Ship
    surface = IMG_Load("picture/ship.png");
    ship = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_DestroySurface(surface);
    SDL_SetTextureScaleMode(ship, SDL_SCALEMODE_NEAREST);

    // Bullet enemy
    surface = IMG_Load("picture/bulletEnemy.png");
    bulletEnemyTexture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_DestroySurface(surface);
    SDL_SetTextureScaleMode(bulletEnemyTexture, SDL_SCALEMODE_NEAREST);
}

LoadRessource::~LoadRessource() {
	if (backgroundLevel1) SDL_DestroyTexture(backgroundLevel1);
	if (backgroundHome) SDL_DestroyTexture(backgroundHome);
	if (bomb) SDL_DestroyTexture(entityTexture);
	if (bulletTexture) SDL_DestroyTexture(bulletTexture);
	if (entityTexture) SDL_DestroyTexture(entityTexture);
	if (heart) SDL_DestroyTexture(heart);
    if (ship) SDL_DestroyTexture(ship);
    if (bulletEnemyTexture) SDL_DestroyTexture(bulletEnemyTexture);
}