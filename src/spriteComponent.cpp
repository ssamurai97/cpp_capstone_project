//
// Created by kuchlong2 on 7/26/20.
//

#include "../include/spriteComponent.h"
#include "../include/shader.h"
#include "../include/actor.h"
#include "../include/texture.h"
#include "../include/game.h"
#include "../include/vertexArray.h"
#include "../include/renderer.h"
#include <glm/gtc/matrix_transform.hpp>
namespace my_game{





Sprite_Component::Sprite_Component(Actor *owner, int draw_order)
  : Component{ owner }, d_texture{ nullptr }, d_draw_order{ draw_order }, d_width{ 0 }, d_height{ 0 }
{
  d_owner->get_game()->get_renderer()->add_sprite(this);
}

Sprite_Component::~Sprite_Component() { d_owner->get_game()->get_renderer()->remove_sprite(this); }



void Sprite_Component::draw(const Shared_Ref<Shader>& shader)
{

  if (d_texture) {

    glm::mat4 sc = glm::scale(glm::mat4(1.0f),glm::vec3(0.5f/static_cast<float>(d_width), 0.5f/static_cast<float>(d_height), 1.0));

       glm::mat4 world = sc * d_owner->get_world_transform();
        shader->set_uniform_mat4f("u_world_transform", world);
       d_texture->bind();
       GLCall((glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr)));

  }
}


void Sprite_Component::set_texture(Shared_Ref<Texture> texture)
{
  d_texture = texture;

  // Set width/height
  d_width = texture->get_width();
  d_height = texture->get_height();
}



void Sprite_Component::draw(const Shared_Ref<Shader> &shader, const Shared_Ref<Vertex_Array> &vertex)
{
  if (d_texture) {

    glm::mat4 sc = glm::scale(glm::mat4(1.0f),glm::vec3(0.5f/static_cast<float>(d_width), 0.5f/static_cast<float>(d_height), 1.0));
    glm::mat4 world= sc * d_owner->get_world_transform();
    shader->set_uniform_mat4f("u_world_transform", world);
    d_texture->bind();
    Renderer::draw_indexed(vertex);
  }
}


}