#include <print>
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h >  

int main(int argc, char** argv)
{

    SDL_Window* window;
    SDL_Renderer* renderer;

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        SDL_Log("Erreur SDL: %s", SDL_GetError());
        return 1;
    }

    if (!SDL_CreateWindowAndRenderer("HELLO SDL", 640, 480, SDL_WINDOW_RESIZABLE, &window, &renderer)) {
        SDL_Log("Erreur création fenêtre/rendu: %s", SDL_GetError());
        return 1;
    }

    // Charger directement une image PNG (pas besoin de IMG_Init)
    SDL_Surface* surface = IMG_Load("arena.png");
    if (!surface) {
        SDL_Log("Erreur chargement image: %s", SDL_GetError());
        return 1;
    }

    SDL_Texture* background = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_DestroySurface(surface);


    bool keepGoing = true;
    do
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_EVENT_QUIT)
                keepGoing = false;
        }

        const double now = ((double)SDL_GetTicks()) / 1000.0;

        const float red = (float)(0.5 + 0.5 * SDL_sin(now));
        const float green = (float)(0.5 + 0.5 * SDL_sin(now + SDL_PI_D * 2 / 3));
        const float blue = (float)(0.5 + 0.5 * SDL_sin(now + SDL_PI_D * 4 / 3));
        SDL_SetRenderDrawColorFloat(renderer, red, green, blue, 1.0f);

        SDL_RenderClear(renderer);

        // 🔥 Dessiner l’image de fond
        SDL_RenderTexture(renderer, background, NULL, NULL);

        // Tu peux ensuite dessiner par-dessus (sprites, etc.)
        SDL_RenderPresent(renderer);
    } while (keepGoing);

    SDL_DestroyTexture(background);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
