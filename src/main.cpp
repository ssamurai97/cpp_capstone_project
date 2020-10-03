
#include "../include/game.h"

int main(){


  if( auto game =my_game::Game(); game.init()){
    game.run_loop();
  }

 return 0;
}