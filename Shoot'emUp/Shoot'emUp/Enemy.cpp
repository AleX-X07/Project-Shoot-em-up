#include "Enemy.h"

Enemy::Enemy() {
	HP = 3;
	Value = 5;
}

Enemy::Enemy(float _x, float _y, float _w, float _h, float _speed, SDL_Color _color) {
	x = _x;
	y = _y;
	w = _w;
	h = _h;
	speed = _speed;
	color = _color;
	Value = 5;
}

int Enemy::randomInt(int min, int max) {
	static std::random_device rd;
	static std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(min, max);
	return dis(gen);
}

void Enemy::updateEnemy(std::vector<Enemy>& enemies, float dt) {
	for (auto& e : enemies) {
		e.x -= e.speed * dt;
		e.rect.x = e.x;
		e.rect.y = e.y;

		// Mise à jour des balles de l'ennemi
		for (auto& b : e.enemiesBullet) {
			b.x += b.vx * dt;
			b.y += b.vy * dt;
		}

		// Supprimer les balles hors écran
		e.enemiesBullet.erase(
			std::remove_if(e.enemiesBullet.begin(), e.enemiesBullet.end(),
				[](const Bullet& b) { return b.x < -100 || b.x > 2000; }),
			e.enemiesBullet.end()
		);
	}

	// Supprimer les ennemis hors écran
	for (int i = enemies.size() - 1; i >= 0; i--) {
		if (enemies[i].x + enemies[i].w < 0) {
			enemies.erase(enemies.begin() + i);
		}
	}
}

void Enemy::renderEnemy(SDL_Renderer* renderer, const std::vector<Enemy>& enemies) {
	for (const auto& e : enemies) {
		if (e.numEnemy == 1) {
			// Rendu de l'ennemi
			SDL_FRect rect = { e.x, e.y, e.w, e.h };
			if (e.enemyTextureBomb) {
				SDL_RenderTexture(renderer, e.enemyTextureBomb, NULL, &rect);
			}
			else {
				SDL_SetRenderDrawColor(renderer, e.color.r, e.color.g, e.color.b, e.color.a);
				SDL_RenderFillRect(renderer, &rect);
			}
		}
		else if (e.numEnemy == 2) {
			// Rendu de l'ennemi
			SDL_FRect rect = { e.x, e.y, e.w, e.h };
			if (e.enemyTextureShooter) {
				SDL_RenderTexture(renderer, e.enemyTextureShooter, NULL, &rect);
			}
			else {
				SDL_SetRenderDrawColor(renderer, e.color.r, e.color.g, e.color.b, e.color.a);
				SDL_RenderFillRect(renderer, &rect);
			}

			// Rendu des balles de l'ennemi
			SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
			for (const auto& b : e.enemiesBullet) {
				SDL_FRect bulletRect = { b.x, b.y, b.w, b.h };
				if (e.bulletEnemyTexture) {
					SDL_RenderTexture(renderer, e.bulletEnemyTexture, NULL, &bulletRect);
				}
				else {
					SDL_SetRenderDrawColor(renderer, e.color.r, e.color.g, e.color.b, e.color.a);
					SDL_RenderFillRect(renderer, &bulletRect);
				}
			}
		}
		
	}
}

void Enemy::spawnEnemyBomb(std::vector<Enemy>& enemies, int windowWidth, int windowHeight, SDL_Renderer* renderer, SDL_Texture* sharedTexture) {
	Enemy e;
	e.numEnemy = 1;
	e.HP = 3;
	e.w = 50;
	e.h = 50;
	e.x = windowWidth;
	e.y = randomInt(0, windowHeight - 50);
	e.rect = { e.x, e.y, e.w, e.h };
	e.enemyTextureBomb = sharedTexture;
	e.speed = 400.0f; // Vitesse en pixels par seconde
	e.lastShotTime = SDL_GetTicks();
	enemies.emplace_back(e);
}

void Enemy::spawnEnemyShooter(std::vector<Enemy>& enemies, int windowWidth, int windowHeight, SDL_Renderer* renderer, SDL_Texture* sharedTexture, SDL_Texture* sharedTextureBulet) {
	Enemy e;
	e.numEnemy = 2;
	e.HP = 5;
	e.w = 75;
	e.h = 75;
	e.x = windowWidth;
	e.y = randomInt(0, windowHeight - 50);
	e.rect = { e.x, e.y, e.w, e.h };
	e.enemyTextureShooter = sharedTexture;
	e.bulletEnemyTexture = sharedTextureBulet;
	e.speed = 200.0f; // Vitesse en pixels par seconde
	e.lastShotTime = SDL_GetTicks();
	enemies.emplace_back(e);
}

void Enemy::shoot(std::vector<Bullet>& enemiesBullet) {
	now = SDL_GetTicks();
	if (now - lastShotTime >= 1500) {
		Bullet b;
		b.x = x;
		b.y = y + h / 2 - 5;
		b.w = 25;
		b.h = 25;
		b.vx = -300.0f; // Vitesse en pixels par seconde
		b.vy = 0;
		b.color = { 255, 255, 0, 255 };
		enemiesBullet.emplace_back(b);
		lastShotTime = now;
	}
}

void Enemy::EnemyManager(std::vector<Enemy>& enemies, SDL_Renderer* renderer, int windowWidth, int windowHeight, LoadRessource& MyRessource, int& nbr_enemies_bomb, int& nbr_enemies_shoot, int& nbr_enemies_shoot_multiple) {
	int choice = randomInt(1,2);
	if (choice == 1 && nbr_enemies_bomb > 0) {
		Enemy::spawnEnemyBomb(enemies, windowWidth, windowHeight, renderer, MyRessource.bomb);
		nbr_enemies_bomb--;
	}
	if (choice == 2 && nbr_enemies_shoot > 0) {
		Enemy::spawnEnemyShooter(enemies, windowWidth, windowHeight, renderer, MyRessource.ship, MyRessource.bulletEnemyTexture);
		nbr_enemies_bomb--;
	}
}

Enemy::~Enemy() {

}