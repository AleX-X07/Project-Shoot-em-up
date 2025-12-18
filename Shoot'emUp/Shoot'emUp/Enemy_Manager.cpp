#include "Enemy_Manager.h"
// Détectoin des enemy sur la durée
EnemyManager::EnemyManager()
    : lastSpawn(SDL_GetTicks()),
    lastShooterEnemySpawn(SDL_GetTicks()),
    lastTripleSpawn(SDL_GetTicks()),
    spawnInterval(2000),
    ShooterEnemySpawnInterval(3000), 
    tripleSpawnInterval(5000) {
}
//Sapwn des enemy en calculant le temps de l'apparition du dernier enemy pour en faire spawn un autre
void EnemyManager::spawn(int windowWidth, int windowHeight, Uint32 now)
{
    if (now - lastSpawn > spawnInterval) {
        Enemy::spawnEnemy(enemies, windowWidth, windowHeight);
        lastSpawn = now;
    }
    if (now - lastShooterEnemySpawn > ShooterEnemySpawnInterval) {
        Shooter_Enemy::spawnShooter_Enemy(Shooter, windowWidth, windowHeight);
        lastShooterEnemySpawn = now;
    }
    if (now - lastTripleSpawn > tripleSpawnInterval) {
        ShootMultiple_Enemy::spawnShootMultiple_Enemy(triples, windowWidth, windowHeight);
        lastTripleSpawn = now;
    }
}
//Update des enemy et des projectiles
void EnemyManager::update(int windowWidth, Uint32 now) {
    for (auto& E : enemies) {
        E.update(windowWidth);
    }

    for (auto& s : Shooter) {
        s.update(windowWidth);
        s.shoot(bullets, now);
    }

    for (auto& t : triples) {
        t.update(windowWidth);
        t.shoot(bullets, now);
    }

    // Nettoyage des ennemis hors écran
    enemies.erase(
        std::remove_if(enemies.begin(), enemies.end(),
            [](const Enemy& e) { return e.x + e.w < 0; }),
        enemies.end()
    );

    Shooter.erase(
        std::remove_if(Shooter.begin(), Shooter.end(),
            [](const Shooter_Enemy& s) { return s.x + s.w < 0; }),
        Shooter.end()
    );


    for (auto& b : bullets) {
        b.x += b.vx;
        b.y += b.vy;
    }
}
//affichage des enemys et des projectiles 
void EnemyManager::render(SDL_Renderer* renderer) {
    for (auto& E : enemies) {
        E.render(renderer);
    }

    for (auto& c : Shooter) {
        c.render(renderer);
    }

    for (auto& t : triples) {
        t.render(renderer);
    }

    SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
    for (auto& b : bullets) {
        SDL_FRect rect = { b.x, b.y, b.w, b.h };
        SDL_RenderFillRect(renderer, &rect);
    }
}
//fonction pour faire disparaitres les projectiles si il atteints la limite de l'ecran
void EnemyManager::cleanBullet() {
    bullets.erase(
        std::remove_if(
            bullets.begin(),
            bullets.end(),
            [](const Bullet& b) { return b.x + b.w < 0; }
        ),
        bullets.end()
    );
}
//Affichage de la barre de vie des enemy
void EnemyManager::renderHealthBar(SDL_Renderer* renderer)
{
    // Fond de la barre (rouge)
    SDL_SetRenderDrawColor(renderer, 100, 0, 0, 255);
    SDL_FRect bgRect = { barX, barY, barWidth, barHeight };
    SDL_RenderFillRect(renderer, &bgRect);

    // Barre de vie (vert)
    float healthPercent = currentHealth / maxHealth;
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    SDL_FRect healthRect = { barX, barY, barWidth * healthPercent, barHeight };
    SDL_RenderFillRect(renderer, &healthRect);

    // Contour de la barre (noir)
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderRect(renderer, &bgRect);
}