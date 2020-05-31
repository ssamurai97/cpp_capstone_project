//
// Created by kuchlong on 5/30/20.
//

#ifndef PONG_PADDLE_HPP
#define PONG_PADDLE_HPP
#include "entity.hpp"
namespace pong {
    class Paddle : Public Entity{
    public:
        Paddle(SDL_Renderer* renderer);
        ~Paddle();

        void Update(float delta);
        void Render(float delta);

    private:
        SDL_Texture* texture{nullptr};
    };
}
#endif //PONG_PADDLE_HPP
