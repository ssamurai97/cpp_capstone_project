//
// Created by kuchlong on 5/28/20.
//

#ifndef PONG_GAME_H
#define PONG_GAME_H
#include <SDL2/SDL.h>
#include<spdlog/spdlog.h>
class Game {
public:
    Game();
    ~Game();
    bool initialize();
    void run_loop();

private:

    bool d_is_running;
    SDL_Window* d_window;


};
#endif //PONG_GAME_H
