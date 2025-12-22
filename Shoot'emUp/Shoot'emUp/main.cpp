// Librairie externe
#include <iostream>

// Load SDL
#include <SDL3/SDL.h> 
#include <SDL3_image/SDL_image.h>
#include <SDL3_ttf/SDL_ttf.h>

// Load file
#include "Hero.h"
#include "Screen.h"
#include "Enemy.h"
#include "LoadRessource.h"
#include "Level.h"
#include "Item.h"

int main(int argc, char** argv) {

    // Variable for window
    SDL_Window* window;
    SDL_Renderer* renderer;

    // Object for game
    Enemy MyEnemy;
    Item MyItem;
    Level MyLevel;

    // Variable for time
    const int FPS = 60; 
    const int FRAME_DELAY = 1000 / FPS;
    Uint64 frameStart;
    int frameTime;
    Uint64 last_time = SDL_GetTicks();

    // Variable for loop
    bool restart = false;
    bool keepGoing = true;
    GameState screen = MENU;

    int menuSelection = 0;
    bool enterPressed = false;

    // Initialisation window
    if (SDL_Init(SDL_INIT_VIDEO) < 0 || !SDL_CreateWindowAndRenderer("SHOOT'EM UP", 1920, 1080, SDL_WINDOW_FULLSCREEN, &window, &renderer)) 
        return 1;
    if (TTF_Init() < 0) {
        SDL_Log("Erreur SDL_ttf : %s", SDL_GetError());
        return 1;
    }

    // Loading ressources
    LoadRessource MyRessource = LoadRessource(renderer); 
    MyRessource.loadAllTexture(); 

    // Create player
    Hero player(400, 300, 100, 100, 400);
    player.texture = MyRessource.entityTexture;
    player.bulletTexture = MyRessource.bulletTexture;

    // Load txt for level
    FileManager Level = FileManager("Level/orderLevel.txt"); 

    // GameLoop
    while (keepGoing) { 
        // Loop for restart
        if (restart) {
            MyLevel.restart(player,MyEnemy,MyItem,MyLevel,restart);
        }

        // Delta time : Computes the time elapsed (in seconds) since the previous frame.
        float dt = (SDL_GetTicks() - last_time) / 1000.0f; 
        last_time = SDL_GetTicks();
        frameStart = SDL_GetTicks();
        
        // Check keyboard for choice in menu
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                keepGoing = false;
                screen = QUIT;
            }
            // Function for move in menu
            NavigateMenu(screen, event, menuSelection, enterPressed);
        }

        // Function for game state
        screen = updateGameState(screen, renderer, MyRessource, player, dt, window, MyEnemy.enemies, player.heroBullets, restart, MyLevel, Level, MyItem.itemVector); // Update the game (Menu,Level,PAUSE,VICTORY,GAMEOVER)

        frameTime = SDL_GetTicks() - frameStart;

        if (frameTime < FRAME_DELAY) { // Delay for 60FPS
            SDL_Delay(FRAME_DELAY - frameTime);
        }

        if (screen == QUIT) {
            keepGoing = false;
        }
    }

    // Destroy the window
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}