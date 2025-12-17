#include "Shooter_Enemy.h"
#include <cstdlib>
<<<<<<< HEAD

Shooter_Enemy::Shooter_Enemy()
{
    lastShotTime = 0;
    lastSpawnTime = 0;
=======
Shooter_Enemy::Shooter_Enemy() {

>>>>>>> 6b492029b84388f2ee313662d4a7c317ac7d449f
}
Shooter_Enemy::Shooter_Enemy(float px, float py, float pw, float ph, float ps, int _health, SDL_Color _color)
{
    x = px;
    y = py;
    w = pw;
    h = ph;
    speed = ps;  
    health = _health;
    color = _color;
    lastShotTime = 0; 
    lastSpawnTime = 0;
}

// Déplacement
void Shooter_Enemy::update(int windowWidth) {
    x -= speed; // déplacement vers la gauche
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
// Update de l'enemy pour savoir sa vitesse et la prédéfinir, et de savoir quand les faire disparaitre
void Shooter_Enemy::updateShooter_Enemy(std::vector<Shooter_Enemy>& Shooter) {
    for (auto& s : Shooter) {
        s.x -= s.speed;
    }
    for (int i = Shooter.size() - 1; i >= 0; i--) {
        if (Shooter[i].x + Shooter[i].w < 0) {
            Shooter.erase(Shooter.begin() + i);
        }
    }
}
//spawn du shooter enemy avec ses fonctions de base
void Shooter_Enemy::spawnShooter_Enemy(std::vector<Shooter_Enemy>& Shooter, int windowWidth, int windowHeight) {
    Shooter_Enemy s;
    s.w = 50;
    s.h = 50;
    s.x = windowWidth;
    s.y = randomInt(0, windowHeight - 50);
    s.color = { 0,0,255,255 };
    s.speed = 1;
    Shooter.emplace_back(s);

    // Santé
    int health = 3;
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
        bullets.emplace_back(b);
        lastShotTime = now;
    }
}
