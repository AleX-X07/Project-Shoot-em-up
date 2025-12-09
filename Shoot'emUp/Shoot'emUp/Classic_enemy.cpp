#include "Classic_enemy.h"
#include <cstdlib>


void Classic_enemy::spawnClassicEnemy(std::vector<Classic_enemy>& classics, int windowWidth, int windowHeight) {
    int w = 50;
    int h = 50;
    int x = windowWidth;
    int y = std::rand() % (windowHeight - h);
    int speed = 2;

    classics.emplace_back(x, y, w, h, speed);
}

// Constructeur
Classic_enemy::Classic_enemy(float px, float py, float pw, float ph, float ps)
    : Enemy(px, py, pw, ph, ps), lastShotTime(0) {
}

// Déplacement
void Classic_enemy::update(int windowWidth) {
    x -= speed; // déplacement vers la gauche
}

// Tir
void Classic_enemy::shoot(std::vector<Projectile>& projectiles, Uint32 now) {
    if (now - lastShotTime >= 500) { // toutes les 0.5s
        Projectile p;
        p.x = x;
        p.y = y + h / 2;
        p.w = 10;
        p.h = 5;
        p.speed = -6; // projectile vers la gauche
        projectiles.push_back(p);
        lastShotTime = now;
    }
}

// Rendu
void Classic_enemy::render(SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255); // bleu
    SDL_FRect rect = {
        x,
        y,
        w,
        h
    };
    SDL_RenderFillRect(renderer, &rect);
}