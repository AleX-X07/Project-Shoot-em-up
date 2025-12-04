#include <print>
#include <SDL3/SDL.h>

int main(int argc, char** argv)
{
    SDL_Window* window;
    SDL_Renderer* renderer;

    SDL_SetAppMetadata("SDL Test", "1.0", "games.anakata.test-sdl");
    if (!SDL_Init(SDL_INIT_VIDEO))
        return 1;

    if (!SDL_CreateWindowAndRenderer("HELLO SDL", 640, 480, SDL_WINDOW_RESIZABLE, &window, &renderer))
        return 1;

    SDL_SetRenderLogicalPresentation(renderer, 640, 480, SDL_LOGICAL_PRESENTATION_LETTERBOX);

    // Position et taille de l'élément
    SDL_FRect rect = { 400.0f, 300.0f, 50.0f, 50.0f };

    // Vitesse de déplacement
    float speed = 200.0f; // pixels par seconde
    Uint64 last_time = SDL_GetTicks();

    bool keepGoing = true;
    do
    {
        // Calcul du delta time
        Uint64 current_time = SDL_GetTicks();
        float dt = (current_time - last_time) / 1000.0f;
        last_time = current_time;

        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_EVENT_QUIT)
                keepGoing = false;
        }

        const double now = ((double)SDL_GetTicks()) / 1000.0;  /* convert from milliseconds to seconds. */

        const float red = 0;
        const float green = 0;
        const float blue = 0;
		const bool* keys = SDL_GetKeyboardState(NULL);

        if (keys[SDL_SCANCODE_UP] || keys[SDL_SCANCODE_W]) {
            rect.y -= speed * dt;
        }
        if (keys[SDL_SCANCODE_DOWN] || keys[SDL_SCANCODE_S]) {
            rect.y += speed * dt;
        }
        if (keys[SDL_SCANCODE_LEFT] || keys[SDL_SCANCODE_A]) {
            rect.x -= speed * dt;
        }
        if (keys[SDL_SCANCODE_RIGHT] || keys[SDL_SCANCODE_D]) {
            rect.x += speed * dt;
        }

        if (rect.x < 0) rect.x = 0;
        if (rect.y < 0) rect.y = 0;
        if (rect.x + rect.w > 640) rect.x = 640 - rect.w;
        if (rect.y + rect.h > 480) rect.y = 480 - rect.h;

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
        SDL_RenderFillRect(renderer, &rect);

		SDL_RenderPresent(renderer);

    } while (keepGoing);

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}