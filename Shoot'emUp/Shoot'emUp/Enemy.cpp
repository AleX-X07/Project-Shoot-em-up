// Load file
#include "Enemy.h"

// Constructor
Enemy::Enemy() {

}

Enemy::Enemy(float _x, float _y, float _w, float _h, float _speed) {
	x = _x;
	y = _y;
	w = _w;
	h = _h;
	speed = _speed;
	Value = 5;
}

// Random : return a int between min and max
int Enemy::randomInt(int min, int max) {
	static std::random_device rd;
	static std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(min, max);
	return dis(gen);
}

// Prevents the enemy to get out of the window
void Enemy::clampToScreenEnemy(int screenWidth, int screenHeight) {
	if (rect.y < 0) {
		rect.y = 0;
	}
	if (rect.y + rect.h > screenHeight) {
		rect.y = screenHeight - rect.h;
	}
}

// Update enemy
void Enemy::updateEnemy(std::vector<Enemy>& enemies, float dt, int w, int h, Hero& player) {
	static bool upOrDown = true;
	for (auto& e : enemies) {
		// Update for boss
		if (e.numEnemy == 10) {
			int width = (w / 4) * 3;
			// First, the boss move in x until 1/4 of window
			if (e.x > width) {
				e.x -= e.speed * dt;
				e.rect.x = e.x;
				e.rect.y = e.y;
			}
			// After, he move in y until one border of window ,and go in the other side after
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
		// Update for other enemies
		else {
			e.x -= e.speed * dt;
			e.rect.x = e.x;
			e.rect.y = e.y;
		}

		// update bullet enemy
		for (auto& b : e.enemiesBullet) {
			b.x += b.vx * dt;
			b.y += b.vy * dt;
		}

		Bullet b;
		b.exploseBullet(w, e.enemiesBullet);

		// Erase bullet off-screen
		for (int i = e.enemiesBullet.size() - 1; i >= 0; i--) {
			if (e.enemiesBullet[i].x < -25) {
				e.enemiesBullet.erase(e.enemiesBullet.begin() + i);
			}
		}
	}

	// Erase enemies off-screen
	for (int i = enemies.size() - 1; i >= 0; i--) {
		if (enemies[i].x + enemies[i].w < 0) {
			enemies.erase(enemies.begin() + i);
			player.nbr_enemy_death++;
		}
	}
}

// Render enemies
void Enemy::renderEnemy(SDL_Renderer* renderer, const std::vector<Enemy>& enemies) {
	for (const auto& e : enemies) {
		SDL_FRect rect = { e.x, e.y, e.w, e.h };
		// Choose the good texture
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

		// If he have texture, render the enemy. Else, display a cube of color
		if (currentTexture) {
			SDL_RenderTexture(renderer, currentTexture, NULL, &rect);
		}
		else {
			SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
			SDL_RenderFillRect(renderer, &rect);
		}

		// Render bullets for enemy 2, 3 and the boss, the enemy 10
		if (e.numEnemy == 2 || e.numEnemy == 3 || e.numEnemy == 10) {
			for (const auto& b : e.enemiesBullet) {
				SDL_FRect bulletRect = { b.x, b.y, b.w, b.h };
				// If they have texture, render the bullet. Else, display a cube of color
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

// Spawn for bomb
void Enemy::spawnEnemyBomb(std::vector<Enemy>& enemies, int windowWidth, int windowHeight, SDL_Renderer* renderer, SDL_Texture* sharedTexture) {
	// Create bomb
	Enemy e;
	e.numEnemy = 1;
	e.HP = 3;
	e.HPmax = 3;
	e.Value = 5;
	e.w = 50;
	e.h = 50;
	e.speed = 400.0f;
	e.enemyTextureBomb = sharedTexture;
	e.x = windowWidth;
	e.y = randomInt(0, windowHeight - 50); // Spawn random in axis y
	e.rect = { e.x, e.y, e.w, e.h };
	enemies.emplace_back(e); // Put the bomb in the enemies vector
}

// Spawn for shooter
void Enemy::spawnEnemyShooter(std::vector<Enemy>& enemies, int windowWidth, int windowHeight, SDL_Renderer* renderer, SDL_Texture* sharedTexture, SDL_Texture* sharedTextureBulet) {
	// Create shooter
	Enemy e;
	e.numEnemy = 2;
	e.HP = 5;
	e.HPmax = 5;
	e.Value = 10;
	e.w = 75;
	e.h = 75;
	e.speed = 200.0f;
	e.enemyTextureShooter = sharedTexture;
	e.bulletEnemyTexture = sharedTextureBulet;
	e.lastShotTime = SDL_GetTicks(); // Take time for bullet
	e.x = windowWidth;
	e.y = randomInt(0, windowHeight - 50); // Spawn random in axis y
	e.rect = { e.x, e.y, e.w, e.h };
	enemies.emplace_back(e); // Put the shooter in the enemies vector
}

// Spawn for shooter V2
void Enemy::spawnEnemyShooterV2(std::vector<Enemy>& enemies, int windowWidth, int windowHeight, SDL_Renderer* renderer, SDL_Texture* sharedTexture, SDL_Texture* sharedTextureBulet) {
	// Create enemy
	Enemy e;
	e.numEnemy = 3;
	e.HP = 7;
	e.HPmax = 7;
	e.Value = 10;
	e.w = 75;
	e.h = 75;
	e.speed = 200.0f;
	e.enemyTextureShooter = sharedTexture;
	e.bulletEnemyTexture = sharedTextureBulet;
	e.lastShotTime = SDL_GetTicks(); // Take time for bullet
	e.x = windowWidth; 
	e.y = randomInt(0, windowHeight - 50); // Spawn random in axis y
	e.rect = { e.x, e.y, e.w, e.h };
	enemies.emplace_back(e); // Put the shooter V2 in the enemies vector
}

// Spawn boss
void Enemy::spawnEnemyBoss(std::vector<Enemy>& enemies, int windowWidth, int windowHeight, SDL_Renderer* renderer, LoadRessource& MyRessource) {
	// Create boss
	Enemy e;
	e.numEnemy = 10;
	e.HP = 100;
	e.HPmax = 100;
	e.Value = 50;
	e.w = 400;
	e.h = 400;
	e.speed = 200.0f;
	e.bossTexture = MyRessource.bossTexture;
	e.bulletEnemyTexture = MyRessource.bulletEnemyTexture;
	e.lastShotTime = SDL_GetTicks(); // Take time for bullet
	e.x = windowWidth;
	e.y = windowHeight / 2 - 150; // Spawn the boss in the middle of the window
	e.rect = { e.x, e.y, e.w, e.h };
	enemies.emplace_back(e); // Put the boss in the enemies vector
}

// EnemyManager for manage the spawn of enemies
void Enemy::EnemyManager(std::vector<Enemy>& enemies, SDL_Renderer* renderer, int windowWidth, int windowHeight, LoadRessource& MyRessource, Level& MyLevel) {
	// Random for choose what enemy spawn
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

	// If no enemy, the boss spawning
	if (MyLevel.nbr_enemy == 0 && MyLevel.nbr_shooter == 0 && MyLevel.nbr_shooter_V2 == 0) {
		choice = 10;
	}
	if (enemies.empty()) {
		if (MyLevel.nbr_boss > 0) {
			Enemy::spawnEnemyBoss(enemies, windowWidth, windowHeight, renderer, MyRessource);
			MyLevel.nbr_boss--;
		}
	}
}

// Shoot for shooter
void Enemy::shoot(std::vector<Bullet>& enemiesBullet) {
	// Take time for calculate delay of 1500 between 2 bullet
	now = SDL_GetTicks();
	if (now - lastShotTime >= 1500) {
		// Create bullet
		Bullet b;
		b.x = x;
		b.y = y + h / 2 - 5;
		b.w = 25;
		b.h = 25;
		b.vx = -300.0f; // Speed of the bullet
		b.vy = 0;
		enemiesBullet.emplace_back(b); // Put the bullet in the bullet vector
		lastShotTime = now; // Update time for calculate delay between 2 bullet
	}
}

// Shoot for shooter V2
void Enemy::shootV2(std::vector<Bullet>& enemiesBullet)
{
	// Take time for calculate delay of 1000 between 2 bullet
	now = SDL_GetTicks();
	if (now - lastShotTime >= 1000) {
		// Take the center position
		float centerY = y + h / 2 - 12.5f;
		int _vy = -150; // Bullet direction (-150 : At the top, 0 in the middle and 150 at the bottom)
		for (int X = 0; X <= 2; X++) {
			Bullet b1;
			b1.x = x;
			b1.y = centerY;
			b1.w = 25;
			b1.h = 25;
			b1.vx = -250.0f; // Speed of the bullet
			b1.vy = _vy;
			enemiesBullet.emplace_back(b1); // Put the bullet in the bullet vector
			_vy += 150; // Increas _vy for change the bullet direction
		}
		lastShotTime = now; // Update time for calculate delay between 2 bullet
	}
}

// Shoot for boos
void Enemy::shootBoss(std::vector<Bullet>& enemiesBullet) {
	// Check if the HP boss is above 3/4
	if (HP > (HPmax/4)*3) {
		// Take time for calculate delay of 100 between 2 bullet
		now = SDL_GetTicks();
		if (now - lastShotTime >= 100) {
			// Create bullet
			Bullet b;
			b.x = x;
			b.y = y + h / 2 - 35;
			b.w = 25;
			b.h = 25;
			b.vx = -600; // Speed for bullet
			b.vy = 0;
			enemiesBullet.emplace_back(b); // Put the bullet in the bullet vector
			lastShotTime = now; // Update time for calculate delay between 2 bullet
		}
	}
	// Check if the HP boss is between 1/2 and 3/4
	else if (HP > (HPmax/2) && HP < (HPmax / 4) * 3) {
		int nbr_bullet = 5;
		int anglebullet = -150; // Bullet direction
		float centerY = y + h / 2 - 50;
		// Take time for calculate delay of 1000 between 2 bullet
		now = SDL_GetTicks();
		if (now - lastShotTime >= 1000) {
			for (int X = 0; X <= nbr_bullet; X++) {
				// Create bullet
				Bullet b;
				b.x = x;
				b.y = centerY;
				b.w = 25;
				b.h = 25;
				b.vx = -300.0f; // Speed of bullet
				b.vy = anglebullet;
				enemiesBullet.emplace_back(b); // Put the bullet in the bullet vector
				anglebullet += 75; // Increas anglebullet for change the bullet direction
			}
			lastShotTime = now; // Update time for calculate delay between 2 bullet
		}
	}
	// Check if the HP boss is between 1/2 and 1/4
	else if (HP < HPmax / 2 && HP > HPmax / 4) {
		// Take time for calculate delay of 1500 between 2 bullet
		now = SDL_GetTicks();
		if (now - lastShotTime >= 1500) {
			// Create bullet
			Bullet b;
			b.x = x;
			b.y = y + h / 2 - 35; // Change center because the dimension are different
			b.w = 100;
			b.h = 100;
			b.vx = -300.0f; // Speed of bullet
			b.vy = 0;
			b.shouldExplode = true;
			enemiesBullet.emplace_back(b); // Put the bullet in the bullet vector
			lastShotTime = now; // Update time for calculate delay between 2 bullet
		}
	}
}