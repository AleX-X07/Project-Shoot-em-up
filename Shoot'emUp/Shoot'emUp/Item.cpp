// Load file
#include "Item.h"


// Constructor
Item::Item() {

}

// Render
void Item::renderItem(SDL_Renderer* renderer, std::vector<Item>& item) {
    for (auto& i : item) {
        // If texture existe, dispaly sprite. Else, display cube 
        if (i.itemTexture) {
            SDL_RenderTexture(renderer, i.itemTexture, NULL, &i.rect);
        }
        else {
            SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
            SDL_RenderFillRect(renderer, &i.rect);
        }
    }
}

// Update
void Item::updateItem(std::vector<Item>& item, float dt) {
    for (auto& i : item) {
        // Update each item in x at each frame
        i.x -= i.speed * dt;
        i.rect.x = i.x;
        i.rect.y = i.y;
    }
}

// Check collision with player
void Item::collidePlayer(std::vector<Item>& item, Hero& player) {
    for (auto& i : item) {
        // If item collide, heal player (HP +1) and erase item
        if (SDL_HasRectIntersectionFloat(&i.rect, &player.rect)) {
            player.HP++;
            item.erase(item.begin());
        }
    }
}

// Spawn item
void Item::itemSpawn(std::vector<Item>& item,SDL_Texture* sharedTexture, int windowWidth, int windowHeight) {
    Item i;
    i.w = 25;
    i.h = 25;
    i.speed = 400.0f;
    i.itemTexture = sharedTexture;
    i.x = windowWidth;
    i.y = Enemy::randomInt(0, windowHeight - 25); // Spawn in random y
    i.rect = { i.x, i.y, i.w, i.h };
    item.emplace_back(i); // Put item in vector
}