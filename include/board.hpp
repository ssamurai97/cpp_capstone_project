//
// Created by kuchlong on 6/2/20.
//

#ifndef PONG_BOARD_HPP
#define PONG_BOARD_HPP
#include "entity.hpp"
#include <cstdlib>
namespace pong{
    class Board : public Entity{

    public:
        Board(SDL_Renderer* r);
        ~Board();


        void update(float delta);
        void render(float delta);

        float bound_top{};
        float bound_bottom{};

    private:
        SDL_Texture* d_texture{nullptr};

    };
}
#endif //PONG_BOARD_HPP
