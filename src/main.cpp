//
// Created by kuchlong on 5/28/20.
//

#include<fmt/core.h>
#include"../include/game.hpp"

int main(){

    pong::Game g{};
    if(auto success = g.initialize(); success){
        g.run_loop();
    }

}