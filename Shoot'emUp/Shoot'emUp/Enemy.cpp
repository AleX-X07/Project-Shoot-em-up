#include "Enemy.h"

Enemy::Enemy() {

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

void Enemy::clampToScreenEnemy(int screenWidth, int screenHeight) {
	if (rect.y < 0) {
		rect.y = 0;
	}
	if (rect.y + rect.h > screenHeight) {
		rect.y = screenHeight - rect.h;
	}
}

void Enemy::updateEnemy(std::vector<Enemy>& enemies, float dt, int w, int h) {
	static bool upOrDown = true;
	for (auto& e : enemies) {
		if (e.numEnemy == 10) {
			int width = (w / 4) * 3;
			if (e.x > width) {
				e.x -= e.speed * dt;
				e.rect.x = e.x;
				e.rect.y = e.y;
			}
			else {
				if (upOrDown) {
					if (e.rect.y == 0) {
						upOrDown = false;
					}
					e.y -= e.speed * dt;
					e.rect.x = e.x;
					e.rect.y = e.y;
					e.clampToScreenEnemy(w, h);
					e.x = e.rect.x;
					e.y = e.rect.y;
				}
				else {
					if (e.rect.y == h-e.rect.h) {
						upOrDown = true;
					}
					e.y += e.speed * dt;
					e.rect.x = e.x;
					e.rect.y = e.y;
					e.clampToScreenEnemy(w, h);
					e.x = e.rect.x;
					e.y = e.rect.y;
				}
			}
		}
		else {
			e.x -= e.speed * dt;
			e.rect.x = e.x;
			e.rect.y = e.y;
		}

		// Mise à jour des balles de l'ennemi
		for (auto& b : e.enemiesBullet) {
			b.x += b.vx * dt;
			b.y += b.vy * dt;
		}

		Bullet b;
		b.exploseBullet(w, e.enemiesBullet);

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
		// Rendu de l'ennemi
		SDL_FRect rect = { e.x, e.y, e.w, e.h };

		// Sélection de la texture appropriée
		SDL_Texture* currentTexture = nullptr;
		if (e.numEnemy == 1) {
			currentTexture = e.enemyTextureBomb;
		}
		else if (e.numEnemy == 2) {
			currentTexture = e.enemyTextureShooter;
		}
		else if (e.numEnemy == 3) {
			currentTexture = e.enemyTextureShooter;
		}
		else if (e.numEnemy == 10) {
			currentTexture = e.bossTexture;
		}

		// Affichage de l'ennemi
		if (currentTexture) {
			SDL_RenderTexture(renderer, currentTexture, NULL, &rect);
		}
		else {
			SDL_SetRenderDrawColor(renderer, e.color.r, e.color.g, e.color.b, e.color.a);
			SDL_RenderFillRect(renderer, &rect);
		}

		// Rendu des balles pour les ennemis qui tirent (numEnemy 2, 3 ou -1)
		if (e.numEnemy == 2 || e.numEnemy == 3 || e.numEnemy == 10) {
			for (const auto& b : e.enemiesBullet) {
				SDL_FRect bulletRect = { b.x, b.y, b.w, b.h };
				if (e.bulletEnemyTexture) {
					SDL_RenderTexture(renderer, e.bulletEnemyTexture, NULL, &bulletRect);
				}
				else {
					SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
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
	e.HPmax = 3;
	e.Value = 5;
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
	e.HPmax = 5;
	e.Value = 10;
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

void Enemy::spawnEnemyShooterV2(std::vector<Enemy>& enemies, int windowWidth, int windowHeight, SDL_Renderer* renderer, SDL_Texture* sharedTexture, SDL_Texture* sharedTextureBulet) {
	Enemy e;
	e.numEnemy = 3;
	e.HP = 7;
	e.HPmax = 7;
	e.Value = 10;
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

void Enemy::spawnEnemyBoss(std::vector<Enemy>& enemies, int windowWidth, int windowHeight, SDL_Renderer* renderer, LoadRessource& MyRessource) {
	Enemy e;
	e.numEnemy = 10;
	e.HP = 100;
	e.HPmax = 100;
	e.Value = 50;
	e.w = 400;
	e.h = 400;
	e.x = windowWidth;
	e.y =  windowHeight / 2 - 150;
	e.rect = { e.x, e.y, e.w, e.h };
	e.bossTexture = MyRessource.bossTexture;
	e.bulletEnemyTexture = MyRessource.bulletEnemyTexture;
	e.speed = 200.0f; // Vitesse en pixels par seconde
	e.lastShotTime = SDL_GetTicks();
	enemies.emplace_back(e);
}

void Enemy::EnemyManager(std::vector<Enemy>& enemies, SDL_Renderer* renderer, int windowWidth, int windowHeight, LoadRessource& MyRessource, Level& MyLevel) {
	int choice = randomInt(1,3);
	if (choice == 1 && MyLevel.nbr_enemy > 0) {
		Enemy::spawnEnemyBomb(enemies, windowWidth, windowHeight, renderer, MyRessource.bomb);
		MyLevel.nbr_enemy--;
	}
	if (choice == 2 && MyLevel.nbr_shooter > 0) {
		Enemy::spawnEnemyShooter(enemies, windowWidth, windowHeight, renderer, MyRessource.ship, MyRessource.bulletEnemyTexture);
		MyLevel.nbr_shooter--;
	}
	if (choice == 3 && MyLevel.nbr_shooter_V2 > 0) {
		Enemy::spawnEnemyShooterV2(enemies, windowWidth, windowHeight, renderer, MyRessource.ship, MyRessource.bulletEnemyTexture);
		MyLevel.nbr_shooter_V2--;
	}
	if (MyLevel.nbr_enemy == 0 && MyLevel.nbr_shooter == 0 && MyLevel.nbr_shooter_V2 == 0) {
		choice = 10;
	}
	if (enemies.empty()) {
		if (choice == 10 && MyLevel.nbr_boss > 0) {
			Enemy::spawnEnemyBoss(enemies, windowWidth, windowHeight, renderer, MyRessource);
			MyLevel.nbr_boss--;
		}
	}
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

void Enemy::shootV2(std::vector<Bullet>& enemiesBullet)
{
	now = SDL_GetTicks();
	if (now - lastShotTime >= 1500) {
		float centerY = y + h / 2 - 12.5f;

		// In front
		Bullet b1;
		b1.x = x;
		b1.y = centerY;
		b1.w = 25;
		b1.h = 25;
		b1.vx = -300.0f;
		b1.vy = 0;
		b1.color = { 255, 255, 0, 255 };
		enemiesBullet.emplace_back(b1);

		// Up (angle ~30°)
		Bullet b2;
		b2.x = x;
		b2.y = centerY;
		b2.w = 25;
		b2.h = 25;
		b2.vx = -300.0f;
		b2.vy = -150.0f;
		b2.color = { 255, 255, 0, 255 };
		enemiesBullet.emplace_back(b2);

		// Down (angle ~30°)
		Bullet b3;
		b3.x = x;
		b3.y = centerY;
		b3.w = 25;
		b3.h = 25;
		b3.vx = -300.0f;
		b3.vy = 150.0f;
		b3.color = { 255, 255, 0, 255 };
		enemiesBullet.emplace_back(b3);

		lastShotTime = now;
	}
}

void Enemy::shootBoss(std::vector<Bullet>& enemiesBullet) {
	if (HP > (HPmax/4)*3) {
		now = SDL_GetTicks();
		if (now - lastShotTime >= 100) {
			Bullet b;
			b.x = x;
			b.y = y + h / 2 - 35;
			b.w = 25;
			b.h = 25;
			b.vx = -600; // Vitesse en pixels par seconde
			b.vy = 0;
			b.color = { 255, 255, 0, 255 };
			enemiesBullet.emplace_back(b);
			lastShotTime = now;
		}
	}
	else if (HP > (HPmax/2) && HP < (HPmax / 4) * 3) {
		int nbr_bullet = 5;
		int anglebullet = -150;
		float centerY = y + h / 2 - 50;
		now = SDL_GetTicks();
		if (now - lastShotTime >= 1000) {
			for (int X = 0; X <= nbr_bullet; X++) {
				Bullet b;
				b.x = x;
				b.y = centerY;
				b.w = 25;
				b.h = 25;
				b.vx = -300.0f;
				b.vy = anglebullet;
				b.color = { 255, 255, 0, 255 };
				enemiesBullet.emplace_back(b);
				anglebullet += 75;
			}
			lastShotTime = now;
		}
	}
	else if (HP < HPmax / 2 && HP > HPmax / 4) {
		now = SDL_GetTicks();
		if (now - lastShotTime >= 3000) {
			Bullet b;
			b.x = x;
			b.y = y + h / 2 - 35;
			b.w = 100;
			b.h = 100;
			b.vx = -300.0f;
			b.vy = 0;
			b.color = { 255, 255, 0, 255 };
			b.shouldExplose = true;
			enemiesBullet.emplace_back(b);
			lastShotTime = now;
		}
	}
}

Enemy::~Enemy() {

}