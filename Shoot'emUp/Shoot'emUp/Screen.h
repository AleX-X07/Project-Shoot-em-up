#pragma once
// Librairie externe
#include <iostream>
#include <vector>

// Load SDL
#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>

// Load file
#include "Hero.h"
#include "Enemy.h"
#include "Menu.h"
#include "Bullet.h"
#include "LoadRessource.h"
#include "Level.h"
#include "FileManager.h"

// Enum for game state
enum GameState {
    MENU,
    LEVEL,
    PAUSE,
    GAMEOVER,
    VICTORY,
    QUIT
};

// Function for navigate in menu
void NavigateMenu(GameState screen, SDL_Event event, int menuSelection, bool enterPressed);

// Function for the game state
GameState updateGameState(GameState screen, SDL_Renderer* renderer, LoadRessource& MyRessource, Hero& player, float dt, SDL_Window* window, std::vector<Enemy>& enemies, std::vector<Bullet>& bullets,bool& restart, Level& MyLevel, FileManager& Level, std::vector<Item>& item);

