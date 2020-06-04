//
// Created by kuchlong on 5/28/20.
//

#include "../include/game.hpp"
namespace pong {
    Game::Game() :
            d_is_running{true}
            ,d_window{nullptr}
            ,d_render{nullptr}{}

    bool Game::initialize() {

        if (auto sdl_result = SDL_Init(SDL_INIT_VIDEO); sdl_result != 0) {
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

        if (!d_window) {
            spdlog::error("Failed to create window {} ", SDL_GetError());
            return false;
        }

        if(d_render = SDL_CreateRenderer(d_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC); != d_render){
            spdlog::error("Failed to create render {} ", SDL_GetError());
            return false;
        }

        lasttick = SDL_GetTicks();
        fpstick = lasttick;
        fps = 0;
        framecount = 0;

        return true;
    }


    void Game::run_loop() {

        while (d_is_running) {

        }
    }
}