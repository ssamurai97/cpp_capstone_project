//
// Created by kuchlong on 5/30/20.
//

#include "../include/ball.hpp"
namespace pong{
    Ball::Ball(SDL_Renderer *renderer):
    Entity(renderer){
        SDL_Surface* surface = IMG_Load("../assets/ball.png");
        d_ball_texture = SDL_CreateTextureFromSurface(d_enderer, surface);
        SDL_FreeSurface(surface);

        x = 0;
        y = 0;
        width = 24;
        height = 24;

        Set_direction(1, 1);

    }

    Ball::~Ball() {
        SDL_DestroyTexture(d_ball_texture);
    }

    void Ball::update(float delta) {
        // Move the ball, time based
        x += direction_x * delta;
        y += direction_y * delta;
    }

    void Ball::render(float delta) {
        SDL_Rect rect;
        rect.x = static_cast<int>(x + 0.5f); // Round the float to the nearest integer
        rect.y = static_cast<int>(y + 0.5f); // Round the float to the nearest integer
        rect.w = width;
        rect.h = height;
        SDL_RenderCopy(d_enderer, d_ball_texture, 0, &rect);
    }

    void Ball::Set_direction(float dirx, float diry) {
        // Normalize the direction vector and multiply with BALL_SPEED
        float length = sqrt(direction_x* dirx + direction_y * diry);
        this->direction_x = utility::Utility::BALL_SPEED * (dirx / length);
        this->direction_y = utility::Utility::BALL_SPEED * (diry / length);

}