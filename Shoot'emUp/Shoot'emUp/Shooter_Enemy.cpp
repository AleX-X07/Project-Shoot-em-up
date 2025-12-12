#include "Shooter_Enemy.h"
#include <cstdlib>



// Modifie aussi le constructeur pour accepter la santé
Shooter_Enemy::Shooter_Enemy(float px, float py, float pw, float ph, float ps, int health)
    : Enemy(px, py, pw, ph, ps, health, color), lastShotTime(0) {
}

// Déplacement
void Shooter_Enemy::update(int windowWidth) {
    x -= speed; // déplacement vers la gauche
}

// Tir
void Shooter_Enemy::shoot(std::vector<Bullet>& bullets, Uint32 now) {
    if (now - lastShotTime >= 1500) 
    {
        Bullet b;
        b.x = x;
        b.y = y + h / 2;
        b.w = 10;
        b.h = 5;
        b.vx = -6; 
        bullets.push_back(b);
        lastShotTime = now;
    }
}

void Shooter_Enemy::spawnShooter_Enemy(std::vector<Shooter_Enemy>& Shooter, int windowWidth, int windowHeight) {
    
    float px = windowWidth - 50.0f;   
    float py = (rand() % (windowHeight - 50)); 
    float pw = 40.0f;
    float ph = 40.0f;
    float ps = 2.0f;

    // Santé
    int health = 3;

    // Ajout de l’ennemi
    Shooter.push_back(Shooter_Enemy(px, py, pw, ph, ps, health));
}



// Rendu
void Shooter_Enemy::render(SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255); // bleu
    SDL_FRect rect = {
        x,
        y,
        w,
        h
    };
    SDL_RenderFillRect(renderer, &rect);
}

