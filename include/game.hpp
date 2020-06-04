//
// Created by kuchlong on 5/28/20.
//

#ifndef PONG_GAME_HPP
#define PONG_GAME_HPP
#include <memory>
#include <SDL2/SDL.h>
#include <spdlog/spdlog.h>
#include "../include/ball.hpp"
#include "../include/board.hpp"
#include "../include/paddle.hpp"
#include <vector>

namespace pong {
    class Game {
    public:
        Game();
        ~Game();

        bool initialize();
        void run_loop();

    private:

        bool            d_is_running;
        SDL_Window*         d_window;
        SDL_Renderer*       d_render;

        // Timing
        unsigned int        last_tick{};
        unsigned int         fps_tick{};
        unsigned int              fps{};
        unsigned int      frame_count{};

        std::unique_ptr<Board*> board;
        std::vector<Paddle*>    paddle;
        std::unique_ptr<Ball*>  ball;

        void clean();
        void update(float delta);
        void render(float delta);

        void new_game();

        void set_paddleY(int index, float y);
        void check_collisions();
        float get_reflection(int index, float hity);

        void AI(float delta);


    };
}
#endif //PONG_GAME_HPP
