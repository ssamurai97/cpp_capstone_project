//
// Created by kuchlong2 on 8/15/20.
//

#ifndef MY_GAME_CAMERACOMPONENT_H
#define MY_GAME_CAMERACOMPONENT_H

#include <glm/glm.hpp>
#include "component.h"
namespace my_game{
class Camera_component : public Component{
public:
  Camera_component(Actor* owner, int update_order = 200);
  Camera_component(const glm::mat4& projection);

  [[nodiscard]] const glm::mat4& get_projection()const { return d_projection; }

protected:

  void set_view_matrix(const glm::mat4& mat4);
  glm::mat4 d_projection = glm::mat4(1.0f);
};
}
#endif// MY_GAME_CAMERACOMPONENT_H
