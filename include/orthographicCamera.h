//
// Created by kuchlong2 on 8/16/20.
//

#ifndef MY_GAME_ORTHOGRAPHIC_CAMERA_H
#define MY_GAME_ORTHOGRAPHIC_CAMERA_H

#include <glm/glm.hpp>
namespace my_game {
class Orthographic_Camera
{
public:
  Orthographic_Camera(float left, float right, float bottom, float top);

  void set_projection(float left, float right, float bottom, float top);

  [[nodiscard]] const glm::vec3& get_position() const { return d_position; }
  void set_position(const glm::vec3& pos){ d_position = pos; recalculate_view_matrix();}

  [[nodiscard]] float get_rotation() const { return d_rotation;}

  void set_rotation(float rotation){ d_rotation = rotation; recalculate_view_matrix();}

  [[nodiscard]] const glm::mat4& get_projection_matrix()const { return d_projection_matrix;}
  [[nodiscard]] const glm::mat4& get_view_matrix()const { return d_view_matrix;}

  [[nodiscard]] const glm::mat4& get_view_projection_matrix()const { return d_view_project_matrix;}

private:
  void recalculate_view_matrix();
private:
  glm::mat4 d_projection_matrix;
  glm::mat4 d_view_matrix;
  glm::mat4 d_view_project_matrix;

  glm::vec3 d_position{ 0.0f, 0.0f, 0.0f };

  float d_rotation{ 0.0f };
};

}
#endif
