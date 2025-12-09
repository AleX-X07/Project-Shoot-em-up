#pragma once
#include <ctime>

#include "Enemy.h"
#include <vector>
#include <SDL3/SDL.h>

struct Projectile {
    float x, y;
    float w, h;
    float speed;
};

class Classic_enemy : public Enemy
{
public:
    Uint32 lastShotTime;
    bool movingRight; // direction actuelle

    Classic_enemy(float px, float py, float pw, float ph, float ps)
        : Enemy(px, py, pw, ph, ps), lastShotTime(0), movingRight(true) {
    }

    void update(int windowWidth) {
        x -= speed; // déplacement vers la gauche

        // Supprimer l'ennemi s'il sort de l'écran
        if (x + w < 0) {
            // Ici tu peux soit le "désactiver", soit gérer ça dans ton main
            // Exemple : mettre un flag ou l'effacer du vecteur
        }
    }



    // Tir scripté (toutes les 0.5s)
    void shoot(std::vector<Projectile>& projectiles, Uint32 now) {
        if (now - lastShotTime >= 500) { // 500 ms
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
    void render(SDL_Renderer* renderer) {
        SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255); // bleu pour différencier
        SDL_FRect rect = {
            static_cast<float>(x),
            static_cast<float>(y),
            static_cast<float>(w),
            static_cast<float>(h)
        };
        SDL_RenderFillRect(renderer, &rect);
    }
    void initEnemies(std::vector<Enemy>& enemies, Uint32& lastSpawn, Uint32& spawnInterval) {
        std::srand(static_cast<unsigned>(std::time(nullptr))); // initialisation aléatoire
        enemies.clear();                                       // vide le vecteur au départ
        lastSpawn = SDL_GetTicks();                            // temps actuel
        spawnInterval = 2000;                                  // toutes les 2 secondes
    }

};
