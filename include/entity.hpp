//
// Created by kuchlong on 5/31/20.
//

#ifndef PONG_ENTITY_HPP
#define PONG_ENTITY_HPP
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
namespace pong {
    class Entity {
        Entity(SDL_Renderer* renderer);
        virtual ~Entity();

        float x, y, width, height;

        virtual void update(float delta);
        virtual void render(float delta);

        bool Collides(Entity* other);
    protected:
        SDL_Renderer* d_renderer{nullptr};

    };
}
#endif //PONG_ENTITY_H
