//
// Created by kuchlong on 5/28/20.
//

#ifndef PONG_GAME_HPP
#define PONG_GAME_HPP
#include <SDL2/SDL.h>
#include<spdlog/spdlog.h>
namespace pong {
    class Game {
    public:
        Game();

        bool initialize();

        void run_loop();

        void quit();

    private:

        bool d_is_running;
        SDL_Window *d_window;


    };
}
#endif //PONG_GAME_HPP
