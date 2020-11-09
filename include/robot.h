//
// Created by kuchlong on 11/9/20.
//

#ifndef MY_GAME_ROBOT_H
#define MY_GAME_ROBOT_H
#include "./actor.h"
namespace my_game {
class Game;
class Robot : public Actor {
public:
  //ctor
  Robot(Game* game);
};

}
#endif// MY_GAME_ROBOT_H
