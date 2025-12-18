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

void Enemy::updateEnemy(std::vector<Enemy>& enemies) {
	for (auto& e : enemies) {
		e.x -= e.speed;

		e.rect.x = e.x;
		e.rect.y = e.y;
	}
	for (int i = enemies.size() - 1; i >= 0; i--) {
		if (enemies[i].x + enemies[i].w < 0) {
			enemies.erase(enemies.begin() + i);
		}
	}
}

void Enemy::renderEnemy(SDL_Renderer* renderer, const std::vector<Enemy>& enemies) {
		for (const auto& e : enemies) {
			SDL_FRect rect = { e.x, e.y, e.w, e.h };
			if (e.enemyTexture) {
				SDL_RenderTexture(renderer, e.enemyTexture, NULL, &rect);
			}
			else {
				SDL_SetRenderDrawColor(renderer, e.color.r, e.color.g, e.color.b, e.color.a);
				SDL_RenderFillRect(renderer, &rect);
			}
		}
}

void Enemy::spawnEnemy(std::vector<Enemy>& enemies, int windowWidth, int windowHeight, SDL_Renderer* renderer, SDL_Texture* sharedTexture) {
	Enemy e;
	e.w = 50;
	e.h = 50;
	e.x = windowWidth;
	e.y = randomInt(0, windowHeight - 50);
	e.rect = { e.x,e.y,e.w,e.h };
	e.enemyTexture = sharedTexture;
	e.speed = 5;
	enemies.push_back(e);
}

Enemy::~Enemy() {
	
}




