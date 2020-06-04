//
// Created by kuchlong on 6/2/20.
//

#include "../include/board.hpp";

namespace pong{
    Board::Board(SDL_Renderer *render):
    Entity{render},x{0}, y{0},
    width{800}, height{600},
    bound_top{21},
    bound_bottom{600-21}{

        SDL_Surface *surface = IMG_LOAD("../assets/side.png");
        d_texture = SDL_CreateTextureFromSurface(surface);
        SDL_FreeSurface(surface);
        srand(time(0));

    }

    Board::~Board() noexcept {
        SDL_DestroyTexture(d_texture);
    }

    void Board::render(float delta) {
        SDL_Rect dstrect;
        dstrect.x = 0;
        dstrect.y = 0;
        dstrect.w = 800;
        dstrect.h = 21;
        SDL_RenderCopy(renderer, sidetexture, 0, &dstrect);

        dstrect.x = 0;
        dstrect.y = 600-21;
        dstrect.w = 800;
        dstrect.h = 21;
        SDL_RenderCopy(d_enderer, d_texture, 0, &dstrect);
    }

}

