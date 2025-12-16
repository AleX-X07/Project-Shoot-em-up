#include "Enemy.h"
Enemy::Enemy() {
	
}

Enemy::Enemy(float _x, float _y, float _w, float _h, float _speed, int _health, SDL_Color _color) {
	x = _x;
	y = _y;
	w = _w;
	h = _h;
	speed = _speed;
	health = _health;
	color = _color;
}

void Enemy::update(int windowWidth) {
	x -= speed * 1.5f; // déplacement vers la gauche
}

void Enemy::render(SDL_Renderer* renderer) {
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // rouge
	SDL_FRect rect = {
		x,
		y,
		w,
		h
	};
	SDL_RenderFillRect(renderer, &rect);
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
		SDL_SetRenderDrawColor(renderer, e.color.r, e.color.g, e.color.b, e.color.a);
		SDL_RenderFillRect(renderer, &rect);
	}
}

void Enemy::spawnEnemy(std::vector<Enemy>& enemies, int windowWidth, int windowHeight) {
	Enemy e;
	e.w = 50;
	e.h = 50;
	e.x = windowWidth;
	e.y = randomInt(0, windowHeight - 50);
	e.color = { 255,0,0,255 };
	e.speed = 1;
	enemies.emplace_back(e);
}