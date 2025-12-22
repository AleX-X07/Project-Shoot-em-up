#include "Item.h"

Item::Item() {

}

void Item::renderItem(SDL_Renderer* renderer, std::vector<Item>& item) {
    for (auto& i : item) {
        if (i.itemTexture) {
            SDL_RenderTexture(renderer, i.itemTexture, NULL, &i.rect);
        }
        else {
            SDL_SetRenderDrawColor(renderer, i.color.r, i.color.g, i.color.b, i.color.a);
            SDL_RenderFillRect(renderer, &i.rect);
        }
    }
}

void Item::updateItem(std::vector<Item>& item, float dt) {
    for (auto& i : item) {
        i.x -= i.speed * dt;
        i.rect.x = i.x;
        i.rect.y = i.y;
    }
}

void Item::collidePlayer(std::vector<Item>& item, Entity& player) {
    for (auto& i : item) {
        if (SDL_HasRectIntersectionFloat(&i.rect, &player.rect)) {
            player.HP++;
            item.erase(item.begin());
        }
    }
}

void Item::itemSpawn(std::vector<Item>& item,SDL_Texture* sharedTexture, int windowWidth, int windowHeight) {
    Item i;
    i.w = 25;
    i.h = 25;
    i.x = windowWidth;
    i.y = Enemy::randomInt(0, windowHeight - 25);
    i.rect = { i.x, i.y, i.w, i.h };
    i.itemTexture = sharedTexture;
    i.speed = 400.0f;
    item.emplace_back(i);
}