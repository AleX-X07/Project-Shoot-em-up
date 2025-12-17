#include "Menu.h"

Menu::Menu(SDL_Texture* _background) {

    background = _background;
    menuSelection = 0;
    upPressed = false;
    downPressed = false;
    enterPressed = false;
    titleTexture = nullptr;
    playTexture = nullptr;
    quitTexture= nullptr;
}

Menu::~Menu() {
    if (titleTexture) SDL_DestroyTexture(titleTexture);
    if (playTexture) SDL_DestroyTexture(playTexture);
    if (quitTexture) SDL_DestroyTexture(quitTexture);
}

void Menu::TitleMenu(SDL_Renderer* renderer, int w, int h, SDL_Color color, const char* text, TTF_Font* font, int x2, int y2, int w2, int h2) {
    std::string str(text);
    int size = str.size();
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_Surface* texteSurface = TTF_RenderText_Solid(font, text, size, color);
    SDL_Texture* texteTexture = SDL_CreateTextureFromSurface(renderer, texteSurface);
    SDL_DestroySurface(texteSurface);

    SDL_FRect destRect = { x2, y2, w2, h2 };

    SDL_RenderTexture(renderer, texteTexture, NULL, &destRect);
    SDL_DestroyTexture(texteTexture);
}

void Menu::ButtonMenu(SDL_Renderer* renderer, int w, int h, SDL_Color color, const char* text, TTF_Font* font, int x2, int y2, int w2, int h2, int menuSelection, int Selection) {
    std::string str(text);
    size_t size = str.size();

    SDL_FRect Rect = { (float)x2, (float)y2, (float)w2,(float)h2 };

    if (menuSelection == Selection) {
        if (Selection == 1) {
            SDL_SetRenderDrawColor(renderer, 255, 100, 100, 255);  // Rouge pour QUIT
        }
        else {
            SDL_SetRenderDrawColor(renderer, 100, 255, 100, 255);  // Vert pour PLAY
        }
        SDL_RenderFillRect(renderer, &Rect);
    }

    SDL_Surface* texteSurface = TTF_RenderText_Solid(font, text, size, color);
    if (!texteSurface) {
        SDL_Log("Erreur création surface texte: %s", SDL_GetError());
        return;
    }

    int textW = texteSurface->w;
    int textH = texteSurface->h;

    SDL_Texture* texteTexture = SDL_CreateTextureFromSurface(renderer, texteSurface);
    SDL_DestroySurface(texteSurface);

    if (!texteTexture) {
        SDL_Log("Erreur création texture texte: %s", SDL_GetError());
        return;
    }

    SDL_FRect destRect = {
        Rect.x + (Rect.w - textW) / 2.0f,
        Rect.y + (Rect.h - textH) / 2.0f,
        (float)textW,
        (float)textH
    };

    SDL_RenderTexture(renderer, texteTexture, NULL, &destRect);
    SDL_DestroyTexture(texteTexture);

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderRect(renderer, &Rect);
}

GameState Menu::DisplayMenu(SDL_Renderer* renderer, SDL_Window* window, TTF_Font* font, LoadRessource MyRessources) {
    int w, h;

    SDL_Color white = { 255, 255, 255, 255 };


    const bool* keys = SDL_GetKeyboardState(NULL);

    SDL_SetRenderDrawColor(renderer, 0, 0, 50, 255);
    SDL_RenderClear(renderer);
    SDL_GetWindowSize(window, &w, &h);

    if (background) {
        SDL_RenderTexture(renderer, background, NULL, NULL);
    }
    
    TitleMenu(renderer, w, h, white, "SHOOT'EM UP", font, w / 2 - 200, 200, 400, 80);

    ButtonMenu(renderer, w, h, white, "PLAY", font, w / 2 - 100, h / 2 - 60, 200, 50, menuSelection, 0);

    ButtonMenu(renderer, w, h, white, "QUIT", font, w / 2 - 100, h / 2 + 20, 200, 50, menuSelection, 1);

    if (keys[SDL_SCANCODE_UP] || keys[SDL_SCANCODE_W]) {
        if (!upPressed) {
            menuSelection = (menuSelection - 1 + 2) % 2;
            upPressed = true;
        }
    }
    else upPressed = false;

    if (keys[SDL_SCANCODE_DOWN] || keys[SDL_SCANCODE_S]) {
        if (!downPressed) {
            menuSelection = (menuSelection - 1 + 2) % 2;
            downPressed = true;
        }
    }
    else downPressed = false;

    if (keys[SDL_SCANCODE_RETURN]) {
        if (!enterPressed) {
            enterPressed = true;
            if (menuSelection == 0) {
                menuSelection = 0;
                return LEVEL1   ;
            }
            if (menuSelection == 1) {
                return QUIT;
            }
        }
    }
    else enterPressed = false;
    SDL_RenderPresent(renderer);
    return MENU;
}