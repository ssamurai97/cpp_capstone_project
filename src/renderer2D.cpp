//
// Created by kuchlong2 on 8/15/20.
//

#include "../include/renderer2D.h"
#include "../include/vertexArray.h"
#include "../include/shader.h"
#include "../include/renderer.h"
#include <array>
#include <glm/gtc/matrix_transform.hpp>

namespace my_game{

struct Vertex {
  glm::vec3 v_position;
  glm::vec4 v_color;
  glm::vec2 v_texcord;
  float     v_tex_index;


};

struct Renderer2D_Data{
   static const size_t max_quads{100};
   static const size_t max_vertices{max_quads * 4};
   static const size_t max_indices{max_quads * 6};
   static const size_t max_texture_slots{16};

  Shared_Ref<Vertex_Array> q_vertex_array;
  Shared_Ref<Vertex_Buffer>  q_vertex_buffer;
  Shared_Ref<Texture> T_texture;
  Shared_Ref<Shader> Texture_Shader;

  size_t Index_count {0};
  Vertex* Vertex_buffer_base { nullptr};
  Vertex* Vertex_buffer_ptr{ nullptr};

  std::array<Shared_Ref<Texture>, max_texture_slots> texture_slots;
  size_t Texture_slot_index = 1;

  glm::vec4 Q_vertex_postions[4];

};

static Renderer2D_Data d_Data;

void Renderer2D::init()
{
  d_Data.q_vertex_array = Vertex_Array::create();

  d_Data.q_vertex_buffer = Vertex_Buffer::create(d_Data.max_vertices * sizeof(Vertex));
  d_Data.q_vertex_buffer->set_layout({
                                       {Shader_Data_Type::Float3, "a_Position"},
                                       {Shader_Data_Type::Float4, "a_Color"},
                                       {Shader_Data_Type::Float2, "a_Tex_cord"},
                                       {Shader_Data_Type::Float,  "v_TexIndex"}

  });

  d_Data.q_vertex_array->add_vertex_buffer(d_Data.q_vertex_buffer);
  d_Data.Vertex_buffer_base = new Vertex[d_Data.max_vertices];

  auto * indices = new uint32_t [d_Data.max_indices];

  uint32_t offset {0};

  for(uint32_t i {0}; i < d_Data.max_indices; i += 6){
    indices[i + 0 ] = offset + 0;
    indices[i + 1 ] = offset + 1;
    indices[i + 2 ] = offset + 2;

    indices[i + 3 ] = offset + 2;
    indices[i + 4 ] = offset + 3;
    indices[i + 5 ] = offset + 0;

    offset += 4;
  }

  Shared_Ref<Index_Buffer> IB = Index_Buffer::create(indices, d_Data.max_indices);

  d_Data.q_vertex_array->set_index_buffer(IB);
  delete [] indices;

  d_Data.T_texture = Texture::create(1,1);
  uint32_t  texture_data = 0xffffffff;
  d_Data.T_texture->set_data(&texture_data,sizeof(uint32_t));
  int32_t samplers[d_Data.max_texture_slots];
  for(uint32_t i{0}; i < d_Data.max_texture_slots; ++i)
        samplers[i] = i;
  d_Data.Texture_Shader = Shader::create("../../src/shaders/b_texture.glsl");
  d_Data.Texture_Shader->bind();
  d_Data.Texture_Shader->set_uniform_array("u_Textures",samplers, d_Data.max_texture_slots);


  d_Data.texture_slots[0] = d_Data.T_texture;
  d_Data.Q_vertex_postions[0]  =  { -0.5f, -0.5f, 0.0f,  1.0f };
  d_Data.Q_vertex_postions[1]  =  { 0.5,  -0.5f, 0.0f,  1.0f };
  d_Data.Q_vertex_postions[2]  =  { 0.5,  0.5f,  0.0f,  1.0f };
  d_Data.Q_vertex_postions[3]  =  { -0.5, 0.5f,  0.0f,  1.0f };
}

void Renderer2D::begin_scene(const Orthographic_Camera& camera)
{
  d_Data.Texture_Shader->bind();
  d_Data.Texture_Shader->set_uniform_mat4f("u_view_projection", camera.get_view_projection_matrix());
  d_Data.Index_count =0;
  d_Data.Vertex_buffer_ptr = d_Data.Vertex_buffer_base;
  d_Data.Texture_slot_index = 1;


}

void Renderer2D::begin_scene(const Camera_component &camera, const glm::mat4 &transform)
{
  glm::mat4 view_proj = camera.get_projection() * glm::inverse(transform);

  d_Data.Texture_Shader->bind();
  d_Data.Texture_Shader->set_uniform_mat4f("u_view_projection", view_proj);

  d_Data.Index_count =0;
  d_Data.Vertex_buffer_ptr = d_Data.Vertex_buffer_base;

  d_Data.Texture_slot_index= 1;
}


void Renderer2D::end_scene()
{
  auto data_size = (uint32_t) ( (uint8_t*)d_Data.Vertex_buffer_ptr - (uint8_t*)d_Data.Vertex_buffer_base);
  d_Data.q_vertex_buffer->set_data(d_Data.Vertex_buffer_base, data_size);

  flush();
}



void Renderer2D::shut_down() {

  delete [] d_Data.Vertex_buffer_base;
}
void Renderer2D::flush() {
  if(d_Data.Index_count == 0)
    return;;

  for(uint32_t i{0}; i < d_Data.Texture_slot_index; ++i){
    d_Data.texture_slots[i]->bind();
  }
  Renderer::draw_indexed(d_Data.q_vertex_array, d_Data.Index_count);
}

void Renderer2D::reset()
{
  end_scene();

  d_Data.Index_count = 0;
  d_Data.Vertex_buffer_ptr = d_Data.Vertex_buffer_base;
  d_Data.Texture_slot_index = 1;

}


void Renderer2D::draw_quad(const glm::vec3 &pos, const glm::vec2 &size, const Shared_Ref<Texture> &texture, const glm::vec4& color) {


  glm::mat4 transform = glm::translate(glm::mat4(1.0f),pos)
  * glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f});
  draw_quad(transform, texture, color);

}



void Renderer2D::draw_quad(const glm::vec2 &pos, const glm::vec2 &size, const Shared_Ref<Texture> &texture, const glm::vec4& color) {
  draw_quad({ pos.x, pos.y, 0.0f}, size, texture, color);
}



void Renderer2D::draw_quad(const glm::vec2 &pos, const glm::vec2 &size, const glm::vec4 &color) {
  draw_quad({ pos.x, pos.y, 0.0f }, size, color);
}


void Renderer2D::draw_quad(const glm::mat4 &transform, const glm::vec4 &color) {
       size_t vertex_count{4};
       float texture_index{0.0f};
       glm::vec2 text_cords[] = {{0.0f, 0.0f},{ 1.0f, 0.0f}, {1.0f, 1.0f}, {0.0f, 1.0f}};

  if(d_Data.Index_count >= Renderer2D_Data::max_indices)
     reset();
  for(size_t i {0}; i < vertex_count; ++i){
    d_Data.Vertex_buffer_ptr->v_position= transform * d_Data.Q_vertex_postions[i];
    d_Data.Vertex_buffer_ptr->v_color= color;
    d_Data.Vertex_buffer_ptr->v_texcord = text_cords[i];
    d_Data.Vertex_buffer_ptr->v_tex_index = texture_index;
    d_Data.Vertex_buffer_ptr++;
  }
  d_Data.Index_count += 6;
}


void Renderer2D::draw_quad(const glm::mat4& transform, const Shared_Ref<Texture>& texture, const glm::vec4& color){
  constexpr size_t  vertex_count{4};
  constexpr glm::vec2  texture_coords[] {{ 0.0f, 0.0f }, { 1.0f, 0.0f }, { 1.0f, 1.0f }, { 0.0f, 1.0f }};

  if(d_Data.Index_count >= Renderer2D_Data::max_indices)
    reset();
  float texture_index{0.0f};
  for(uint32_t i {1}; i < d_Data.Texture_slot_index; ++i){
    if(*d_Data.texture_slots[i] == *texture){
      texture_index =static_cast<float>(i);
      break;
    }
  }
  if(texture_index == 0.0f){
    if(d_Data.Texture_slot_index >= Renderer2D_Data::max_texture_slots)
      reset();
    texture_index = static_cast<float>(d_Data.Texture_slot_index);
    d_Data.texture_slots[d_Data.Texture_slot_index] = texture;
    d_Data.Texture_slot_index++;
  }
  for(size_t i {0}; i < vertex_count; ++i){
    d_Data.Vertex_buffer_ptr->v_position = transform * d_Data.Q_vertex_postions[i];
    d_Data.Vertex_buffer_ptr->v_color = color;
    d_Data.Vertex_buffer_ptr->v_texcord  = texture_coords[i];
    d_Data.Vertex_buffer_ptr->v_tex_index = texture_index;
  }
  d_Data.Index_count += 6;
}

void Renderer2D::draw_quad(const glm::vec3 &pos, const glm::vec2 &size, const glm::vec4 &color) {
  glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos)
                        * glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f});

  draw_quad(transform, color);
}


}

