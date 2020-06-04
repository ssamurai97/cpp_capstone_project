//
// Created by kuchlong on 5/30/20.
//

#include "../include/paddle.hpp"

namespace pong{
    Paddle::Paddle(SDL_Renderer *renderer)
    : Entity{render}
    ,x{0}
    ,y{0}
    ,width{32}
    ,height{128}
    {
        SDL_Surface* surface = IMG_Load("../assets/paddle.png");
        d_texture = SDL_CreateTextureFromSurface(d_renderer, surface);
        SDL_FreeSurface(surface);
    }


    Paddle::~Paddle() noexcept {
        SDL_DestroyTexture(d_texture);
    }

    void Paddle::Update(float delta) {}

    void Paddle::Render(float delta) {
        SDL_Rect rect;
        rect.x = static_cast<int>(x + 0.5f); // Round the float to the nearest integer
        rect.y = static_cast<int>(y + 0.5f); // Round the float to the nearest integer
        rect.w = width;
        rect.h = height;
        SDL_RenderCopy(d_renderer, d_texture, 0, &rect);
    }


}