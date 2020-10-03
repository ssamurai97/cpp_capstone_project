//
// Created by kuchlong2 on 8/16/20.
//

#include "../include/orthographicCamera.h"
#include <glm/gtc/matrix_transform.hpp>

namespace my_game{

Orthographic_Camera::Orthographic_Camera(float left, float right, float bottom, float top)
:d_projection_matrix{glm::ortho(left, right, bottom, top, -1.0f, 1.0f)}
,d_view_matrix{1.0}
{
  d_view_project_matrix = d_projection_matrix * d_view_matrix;
}

void Orthographic_Camera::set_projection(float left, float right, float bottom, float top)
{
  d_projection_matrix = glm::ortho(left, right, bottom, top, -1.0f, 1.0f);
  d_view_project_matrix = d_projection_matrix * d_view_matrix;
}

void Orthographic_Camera::recalculate_view_matrix()
{
  glm::mat4 transform = glm::translate(glm::mat4(1.0f), d_position) *
   glm::rotate(glm::mat4(1.0f), glm::radians(d_rotation), glm::vec3(0,0, 1));

  d_view_matrix = glm::inverse(transform);

  d_view_project_matrix= d_projection_matrix * d_view_matrix;
}
}