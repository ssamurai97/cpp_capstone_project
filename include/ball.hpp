//
// Created by kuchlong on 5/30/20.
//

#ifndef PONG_BALL_HPP
#define PONG_BALL_HPP
#include"entity.hpp"
#include "utility.hpp"
namespace pong {
    class Ball : public Entity{
    public:
        Ball(SDL_Renderer* renderer);
        ~Ball();

        void update(float delta);
        void render(float delta);

        void set_direction(float x, float y);
        float direction_x{};
        float direction_y{};

    private:
        SDL_Texture* d_ball_texture{nullptr};

    };
}
#endif //PONG_BALL_HPP
