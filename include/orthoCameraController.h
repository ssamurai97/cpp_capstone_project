//
// Created by kuchlong2 on 8/25/20.
//

#ifndef MY_GAME_ORTHOCAMERACONTROLLER_H
#define MY_GAME_ORTHOCAMERACONTROLLER_H
#include "orthographicCamera.h"
namespace my_game {

class Ortho_camera_controller
{
public:

  Ortho_camera_controller(float aspect_ration, bool rotate = false);

  void update(float delta_time);
  Orthographic_Camera& get_camera(){ return d_camera;}
private:
  float d_aspect_ratio;
  float d_zoom_level = 1.0;
  Orthographic_Camera d_camera;
  bool d_rotation;

  glm::vec3 d_camera_position = { 0.0f, 0.0f, 0.0f };

  float d_camera_rotation = 0.0f; //In degrees, in the anti-clockwise direction
  float d_camera_translation_Speed = 5.0f, d_camera_rotation_Speed = 180.0f;


};

}
#endif// MY_GAME_ORTHOCAMERACONTROLLER_H
