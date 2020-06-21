//
// Created by kuchlong on 5/28/20.
//

#include<fmt/core.h>
#include"../include/game.hpp"

int main(){

    //std::unique_ptr<pong::Game> g = std::make_unique<pong::Game>();
    if(auto game = std::make_unique<pong::Game>(); game->initialize()){
        game->run_loop();
    }

   return 0;
}