//
// Created by kuchlong2 on 8/15/20.
//

#ifndef MY_GAME_RENDERER2D_H
#define MY_GAME_RENDERER2D_H
#include "texture.h"
#include "cameraComponent.h"
#include "orthographicCamera.h"

namespace my_game{
class Renderer2D{

public:

  static void init();

  static void shut_down();


  static void begin_scene(const Orthographic_Camera& camera);
  static void begin_scene(const Camera_component& camera, const glm::mat4 &transform);
  static void end_scene();
  static void flush();
  static void draw_quad(const glm::vec2& pos, const glm::vec2& size, const glm::vec4& color);
  static void draw_quad(const glm::vec3& pos, const glm::vec2& size, const glm::vec4& color);

  static void draw_quad(const glm::vec2& pos, const glm::vec2& size, const Shared_Ref<Texture>& texture, const glm::vec4& color);
  static void draw_quad(const glm::vec3& pos, const glm::vec2& size, const Shared_Ref<Texture>& texture, const glm::vec4& color);
  static void draw_quad(const glm::mat4& transform, const Shared_Ref<Texture>& texture, const glm::vec4& color);
  static void draw_quad(const glm::mat4& trans, const glm::vec4& color);

private:
  static void reset();
};

}

#endif// MY_GAME_RENDERER2D_H
