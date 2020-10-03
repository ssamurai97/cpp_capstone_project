//
// Created by kuchlong2 on 8/26/20.
//
#include "../include/cameraComponent.h"
#include "../include/actor.h"
#include "../include/renderer.h"
#include "../include/game.h"
namespace my_game{

Camera_component::Camera_component(Actor* owner, int update_order)
:Component{owner, update_order}
{}

void Camera_component::set_view_matrix(const glm::mat4 &mat4)
{

 // Game* game = d_owner->get_game();
  //game->get_renderer()->set_view_matrix(mat4);
}
}