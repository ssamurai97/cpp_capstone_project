//
// Created by kuchlong on 11/9/20.
//

#include "../include/robot.h"
#include "../include/game.h"
#include "../include/spriteComponent.h"
#include "../include/renderer.h"
namespace my_game{
Robot::Robot(Game *game)
 : Actor(game)
{
  auto sprite_component = new Sprite_Component(this, 150);

  sprite_component->set_texture(game->get_renderer()->get_texture("../../src/images/mech_h.png"));

}
}