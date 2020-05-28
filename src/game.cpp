//
// Created by kuchlong on 5/28/20.
//

#include "../include/game.h"

Game::Game() :
d_is_running{true},
d_window{nullptr}
{}

bool Game::initialize() {

    if(auto sdl_result = SDL_Init(SDL_INIT_VIDEO); sdl_result != 0 ){
        spdlog::error("Unable to initialize SDL {}", SDL_GetError());
        return false;
    }

    //create sdl window
    d_window = SDL_CreateWindow(
            "Pong Game",
            100,
            100,
            1024,
            768,
            0
            );

    if(!d_window){
        spdlog::error("Failed to create window {} ", SDL_GetError());
        return false;
    }

    return true;
}

Game::~Game() {
    if(!d_is_running) {
        SDL_DestroyWindow(d_window);
        SDL_Quit();
    }
}

void Game::run_loop() {

    while (d_is_running)
        {

    }
}