//
// Created by kuchlong2 on 7/26/20.
//

#include "../include/renderer.h"
#include "../include/shader.h"
#include "../include/vertexArray.h"
#include "../include/spriteComponent.h"
#include "../include/renderer2D.h"
#include "../include/texture.h"
#include "../include/resourceManager.h"
#include <glm/gtc/matrix_transform.hpp>
#include <spdlog/spdlog.h>

namespace my_game{


Unique_ptr<Renderer::Scene_data> Renderer::d_scene = create_unique<Renderer::Scene_data>();

Renderer::Renderer(Game* game)
:d_game{game}
,d_shader{ nullptr}
,d_camera{1024.0f/786.0}
,d_project(glm::ortho(0.0f, 0.1f, 0.0f, 0.1f, -1.0f, 1.0f))
{
}

Renderer::~Renderer()
{

  //Renderer2D::shut_down();

  if(d_context)
    SDL_GL_DeleteContext(d_context);
  if(d_window)
    SDL_DestroyWindow(d_window);
  SDL_Quit();
}
void Renderer::init(float width, float height)
{

  d_screen_width = width;
  d_screen_height = height;


  // Set OpenGL attributes
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
  // Specify version
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);

  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
  // Request a color buffer with 8-bits per RGBA channel
  SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
  SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
  SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
  SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
  SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
  // Enable double buffering
  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
  // Force OpenGL to use hardware acceleration
  SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);

  const char* glsl_version = "#version 150";

  Uint32 flags = SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI;
  d_window = SDL_CreateWindow("Game Dev", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                             static_cast<int>(d_screen_width), static_cast<int>(d_screen_height), flags);
  if (!d_window)
  {
    spdlog::error("Failed to create window: %s", SDL_GetError());
  }

  // Create an OpenGL context
  d_context = SDL_GL_CreateContext(d_window);


  // Initialize GLEW
  glewExperimental = GL_TRUE;
  if (glewInit() != GLEW_OK)
  {
    spdlog::error("Failed to initialize GLEW.");

  }

  if(!load_shaders()){
    spdlog::error("failed to load shaders \n");
  }

  create_verts();

  d_texture = Texture::create();

  d_texture->load("../../src/images/mech_h.png");

}
void Renderer::draw(){

  clear_color({0.8f, 0.5f, 0.5f, 1.0f});
  // Clear the color buffer
  clear();
  // Enable depth buffering/disable alpha blend
  enable_gl_blend();
  begin_scene(d_camera.get_camera());
  d_texture->bind();
  submit(d_shader, d_vertex_array);

  SDL_GL_SwapWindow(d_window);
}


void Renderer::create_verts()
{


  float vertices[] = {
    -0.5f, -0.5f,  0.0f, 0.0f, 0.0f,
     0.5,  -0.5f,  0.0f, 1.0f, 0.0f,
     0.5,   0.5f,  0.0f, 1.0f, 1.0f,
    -0.5,   0.5f,  0.0f, 0.0f, 1.0f
  };

  uint32_t indices [] = {
    0, 1, 2,
    2, 3, 0
  };

  d_vertex_array = Vertex_Array::create();

  d_vertex_buffer = Vertex_Buffer::create(vertices,sizeof(vertices));

  d_vertex_buffer->set_layout({{Shader_Data_Type::Float3,"a_Position"},
                               {Shader_Data_Type::Float2,"a_TexCord"}});

  d_vertex_array->add_vertex_buffer(d_vertex_buffer);
  Shared_Ref<Index_Buffer> IB;
  IB = Index_Buffer::create(indices,sizeof(indices));
  d_vertex_array->set_index_buffer(IB);

}




void Renderer::begin_scene(Orthographic_Camera &camera)
{
 d_scene->d_view_project = camera.get_view_projection_matrix();
}

void Renderer::submit(const Shared_Ref<Shader> &shader, const Shared_Ref<Vertex_Array> &vertex_array)
{
  shader->bind();
  shader->set_uniform_mat4f("u_view",d_scene->d_view_project);
  vertex_array->bind();
  Renderer::draw_indexed(vertex_array);
}



void Renderer::draw_indexed(const Shared_Ref<Vertex_Array> &vertex_array, uint32_t index) {

  uint32_t count = index ? index : vertex_array->get_index_buffer()->get_count();
  glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, nullptr);
  glBindTexture(GL_TEXTURE_2D, 0);
}


bool Renderer::load_shaders() {
  d_shader = Shader::create("../../src/shaders/Texture.glsl");

  return true;
}


void Renderer::add_sprite(Sprite_Component* sprite) {
  auto drawn_order = sprite->get_update_order();
  auto iter = d_sprites.begin();
  for (;
    iter != d_sprites.end();
    ++iter)
  {
    if (drawn_order < (*iter)->get_update_order())
    {
      break;
    }
  }

  // Inserts element before position of iterator
  d_sprites.insert(iter, sprite);

}
void Renderer::remove_sprite(Sprite_Component* sprite) {
  auto iter = std::find(d_sprites.begin(), d_sprites.end(), sprite);
  d_sprites.erase(iter);
}

Shared_Ref<Texture> Renderer::get_texture(const std::string &file_name) {
  Shared_Ref<Texture> texture{nullptr};

  auto itr = d_textures.find(file_name);
  if(itr != d_textures.end()){
    texture = itr->second;
  } else{
    texture = Texture::create();
    if(texture->load(file_name)){
      d_textures.emplace(file_name, texture);
    } else{
      texture = nullptr;
    }
  }
  return texture;
}


void Renderer::enable_gl_blend() {

  glEnable(GL_DEPTH_TEST);
  glDisable(GL_BLEND);

  glEnable(GL_BLEND);
  glBlendEquationSeparate(GL_FUNC_ADD, GL_FUNC_ADD);
  glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ZERO);
}



void Renderer::clear_color(const glm::vec4& color) {
  glClearColor(color.r, color.g, color.b, color.a);
}

void Renderer::clear() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}


}
