//
// Created by kuchlong on 5/31/20.
//

#include "../include/entity.hpp"


Entity::Entity(SDL_Renderer* renderer):
d_render{render},
x{0},y{0},width{1}, height{1}
{

}

Entity::~Entity() {
}

Entity::~Entity() {
}

void Entity::Update(float delta) {
}

void Entity::Render(float delta) {
}


bool Entity::Collides(Entity* other) {
    if (x + width > other->x && x < other->x + other->width &&
        y + height > other->y && y < other->y + other->height) {
        return true;
    }
    return false;
}
