// Librairie externe
#include <iostream>

// Load fiele
#include "Menu.h"

// Function for write on screen
void Texte(SDL_Renderer* renderer, int w, int h, SDL_Color color, const char* text, TTF_Font* font, int x2, int y2, int w2, int h2) {
    std::string str(text);
    size_t size = str.size();
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_Surface* texteSurface = TTF_RenderText_Solid(font, text, size, color);
    SDL_Texture* texteTexture = SDL_CreateTextureFromSurface(renderer, texteSurface);
    SDL_DestroySurface(texteSurface);

    SDL_FRect destRect = { x2, y2, w2, h2 };

    // Display text
    SDL_RenderTexture(renderer, texteTexture, NULL, &destRect);
    SDL_DestroyTexture(texteTexture);
}

// Function for display button
void Button(SDL_Renderer* renderer, int w, int h, SDL_Color color, const char* text, TTF_Font* font, float x2, float y2, float w2, float h2, int menuSelection, int Selection) {
    std::string str(text);
    size_t size = str.size();

    SDL_FRect Rect = { x2, y2, w2,h2 };

    // Change color if player is in menu (green) or in quit (red)
    if (menuSelection == Selection) {
        if (Selection == 1) {
            SDL_SetRenderDrawColor(renderer, 255, 100, 100, 255); 
        }
        else {
            SDL_SetRenderDrawColor(renderer, 100, 255, 100, 255);
        }
        SDL_RenderFillRect(renderer, &Rect);
    }

    // Create surface for display text
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

    // Display button
    SDL_RenderTexture(renderer, texteTexture, NULL, &destRect);
    SDL_DestroyTexture(texteTexture);

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderRect(renderer, &Rect);
}