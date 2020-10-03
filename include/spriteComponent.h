//
// Created by kuchlong2 on 7/26/20.
//

#ifndef MY_GAME_SPRITE_COMPONENT_H
#define MY_GAME_SPRITE_COMPONENT_H
#include "component.h"
#include "util.h"
#include <glm/glm.hpp>
namespace my_game{
class Shader;
class Vertex_Array;
class Texture;

// Class representing a drawable sprite. A sprite can have multiple frames, for
// animation.
class Sprite_Component : public Component
{
public:
  explicit Sprite_Component(Actor* owner, int draw_order = 100);

  ~Sprite_Component();

  virtual void draw(const Shared_Ref<Shader>& shader);

  virtual void set_texture(Shared_Ref<Texture> texture);

  void draw(const Shared_Ref<Shader>& shader, const Shared_Ref<Vertex_Array>& vertex);

  [[nodiscard]] int get_draw_order() const { return d_draw_order; }
  [[nodiscard]] int get_width() const { return d_width; }
  [[nodiscard]] int get_height() const { return d_height; }


  [[nodiscard]] TypeID get_type()const override { return  SPRITE_COMPONENT; }

private:
  Shared_Ref<Texture> d_texture;
  int                 d_draw_order;
  int                 d_width;
  int                 d_height;
};
}

#endif// MY_GAME_SPRITE_COMPONENT_H
