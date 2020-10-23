//
// Created by kuchlong2 on 8/25/20.
//

#include "../include/orthoCameraController.h"
#include <SDL2/SDL.h>

namespace my_game{

Ortho_camera_controller::Ortho_camera_controller( float aspect_ration, bool rotate)
:d_aspect_ratio{aspect_ration}, d_camera{-d_aspect_ratio * d_zoom_level, d_aspect_ratio * d_zoom_level, -d_zoom_level, d_zoom_level}
,d_rotation{rotate}{}

void Ortho_camera_controller::update(float delta_time)
{
  auto *state = SDL_GetKeyboardState(nullptr);
  if(state[SDL_SCANCODE_A]){
    d_camera_position.x -= cos(glm::radians(d_camera_rotation)) * d_camera_translation_Speed * delta_time;
    d_camera_position.y -= sin(glm::radians(d_camera_rotation)) * d_camera_translation_Speed * delta_time;
  }else if(state[SDL_SCANCODE_D]){
    d_camera_position.x += cos(glm::radians(d_camera_rotation)) * d_camera_translation_Speed * delta_time;
    d_camera_position.y += sin(glm::radians(d_camera_rotation)) * d_camera_translation_Speed * delta_time;
  }

  if(state[SDL_SCANCODE_W]){
    d_camera_position.x += -sin(glm::radians(d_camera_rotation)) * d_camera_translation_Speed * delta_time;
    d_camera_position.y += cos(glm::radians(d_camera_rotation)) * d_camera_translation_Speed * delta_time;
  }else if(state[SDL_SCANCODE_S]){
    d_camera_position.x -= -sin(glm::radians(d_camera_rotation)) * d_camera_translation_Speed * delta_time;
    d_camera_position.y -= cos(glm::radians(d_camera_rotation)) * d_camera_translation_Speed * delta_time;
  }

  if(d_rotation){
    if(state[SDL_SCANCODE_W])
      d_camera_position += d_camera_rotation_Speed * delta_time;
    if(state[SDL_SCANCODE_E])
      d_camera_rotation -= d_camera_rotation_Speed * delta_time;
    if(d_camera_rotation > 180.0f)
      d_camera_rotation -= 360.0f;
    else if(d_camera_rotation <= -180.0f)
      d_camera_rotation += 360.0f;
    d_camera.set_rotation(d_camera_rotation);
  }
  d_camera.set_position(d_camera_position);

  d_camera_translation_Speed = d_zoom_level;
}
}