#include "Level.h"
#include "Enemy.h"


Level::Level() {
    numLevel = 1;
	nbr_enemy = 0;
	nbr_shooter = 0;
	nbr_shooter_V2 = 0;
	nbr_boss = 0;
	levelWithBoss = false;
}

void Level::setMyLevel(int _nbr_enemy, int _nbr_shooter, int _nbr_shooter_V2, int _nbr_boss) {
	nbr_enemy = _nbr_enemy;
	nbr_shooter = _nbr_shooter;
	nbr_shooter_V2 = _nbr_shooter_V2;
	nbr_boss = _nbr_boss;
	if (_nbr_boss > 0) {
		levelWithBoss = true;
	}
    nbr_enemy_total = _nbr_enemy;
    nbr_shooter_total = _nbr_shooter;
    nbr_shooter_V2_total = _nbr_shooter_V2;
    nbr_boss_total = _nbr_boss;
}

int Level::typeLevel(Entity& player) {
	if (levelWithBoss) {
		if (player.bossDeath == nbr_boss_total) {
            levelWithBoss = false;
			return 1;
		}
	}
	else {
		if (player.nbr_enemy_death == (nbr_enemy_total + nbr_shooter_total + nbr_shooter_V2_total)) {
			return 1;
		}
	}
	return 0;
}

void Level::displayLevel(SDL_Renderer* renderer, LoadRessource& MyRessource, Entity& player, float dt, SDL_Window* window, std::vector<Enemy>& enemies, std::vector<Bullet>& bullets, Level& MyLevel, const bool* keys, int w, int h) {
    
    player.handleInput(keys, dt);
    SDL_GetWindowSize(window, &w, &h);
    player.clampToScreen(w, h);
    player.updateBullets(dt, player.heroBullets);

    spawnTimer += dt; // Spawn enemies
    if (spawnTimer >= spawnInterval) {
        Enemy::EnemyManager(enemies, renderer, w, h, MyRessource, MyLevel);
        spawnTimer = 0;
    }

    Enemy::updateEnemy(enemies, dt, w, h);

    for (auto& e : enemies) { // Shoot for enemies
        if (e.numEnemy == 2) {
            e.shoot(e.enemiesBullet);
        }
        else if (e.numEnemy == 3) {
            e.shootV2(e.enemiesBullet);
        }
        else if (e.numEnemy == 10) {
            e.shootBoss(e.enemiesBullet);
        }
    }

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    SDL_RenderTexture(renderer, MyRessource.backgroundLevel1, NULL, NULL);

    player.render(renderer);
    player.renderBullets(renderer, player.heroBullets);
    Enemy::renderEnemy(renderer, enemies);
    player.HUD(renderer, MyRessource.heart, player.HP, player.Score);

    player.CollideEnemy(enemies, dt);
    player.CollideEnemyBullet(enemies, dt);
    player.CollideBullet(enemies);

    SDL_RenderPresent(renderer);
}

void Level::reset(Entity& player, std::vector<Enemy>& enemies) {
    player.HP = 4;
    player.heroBullets.clear();
    enemies.clear();
    player.rect.x = 400.0f;
    player.rect.y = 300.0f;
    spawnTimer = 0;
}