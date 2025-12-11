#include "Enemy.h"

void updateEnemies(std::vector<Enemy>& enemies) {
    for (auto& e : enemies) {
        e.x -= e.speed;
    }
    enemies.erase(std::remove_if(enemies.begin(), enemies.end(),
        [](const Enemy& e) { return e.x + e.w < 0; }),
        enemies.end());
}
void renderEnemies(SDL_Renderer* renderer, const std::vector<Enemy>& enemies) {
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); //Image de l'ennemie
    for (auto& e : enemies) {
        SDL_FRect rect = {
    static_cast<float>(e.x),
    static_cast<float>(e.y),
    static_cast<float>(e.w),
    static_cast<float>(e.h)
        };
        SDL_RenderFillRect(renderer, &rect); 

    }
}
void spawnEnemy(std::vector<Enemy>& enemies, int windowWidth, int windowHeight) {
    Enemy e;
    e.w = 50;
    e.h = 50;
    e.x = windowWidth; // apparaît à droite
    e.y = std::rand() % (windowHeight - static_cast<int>(e.h));
    e.speed = 3 + std::rand() % 5;
    enemies.push_back(e);
}