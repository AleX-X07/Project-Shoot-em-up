#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include "Hero.h"

int main(int argc, char** argv) {
    SDL_Window* window;
    SDL_Renderer* renderer;
    int w;
    int h;
    if (SDL_Init(SDL_INIT_VIDEO) < 0 || !SDL_CreateWindowAndRenderer("HELLO SDL", 640, 480, SDL_WINDOW_FULLSCREEN, &window, &renderer)) return 1;

    SDL_Surface* surface = IMG_Load("arena.png");
    SDL_Texture* background = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_DestroySurface(surface);

    Entity player(400.0f, 300.0f, 100.0f, 100.0f, SDL_Color{ 255, 0, 0, 255 });
    player.loadTexture(renderer, "player.png");

    Uint64 last_time = SDL_GetTicks();
    bool keepGoing = true;
    while (keepGoing) {
        float dt = (SDL_GetTicks() - last_time) / 1000.0f;
        last_time = SDL_GetTicks();
        SDL_Event event;
        while (SDL_PollEvent(&event)) if (event.type == SDL_EVENT_QUIT) keepGoing = false;
        player.handleInput(SDL_GetKeyboardState(NULL), dt);
        SDL_GetWindowSize(window, &w, &h);
        player.clampToScreen(w, h);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        SDL_RenderTexture(renderer, background, NULL, NULL);
        player.render(renderer);
        SDL_RenderPresent(renderer);
    }
    SDL_DestroyTexture(background);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}