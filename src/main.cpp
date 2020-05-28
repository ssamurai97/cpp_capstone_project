//
// Created by kuchlong on 5/28/20.
//

#include<fmt/core.h>
#include"../include/game.h"

int main(){

    Game g{};
    if(auto success = g.initialize(); success){
        g.run_loop();
    }

}