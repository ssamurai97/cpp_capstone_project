//
// Created by kuchlong2 on 7/26/20.
//

#ifndef MY_GAME_RENDERER_H
#define MY_GAME_RENDERER_H
#include <string>
#include <GL/glew.h>
#include <vector>
#include "util.h"
#include <unordered_map>
#include "orthoCameraController.h"
#include "orthographicCamera.h"
#ifdef __APPLE__
#include <SDL.h>
#else
#include <SDL2/SDL.h>
#endif

namespace my_game {
class  Game;
class  Sprite_Component;
class  Texture;
class  Vertex_Array;
class  Vertex_Buffer;
class  Shader;
class  Renderer
{
public:

  //Constructors
  explicit Renderer(Game *game);
  ~Renderer();


  // Accessors
  void          init(float width, float height);
  void          shut_down();
  void          draw();

  static void   enable_gl_blend();
  static void   clear_color(const glm::vec4& color);
  static void   clear();
  void          add_sprite( Sprite_Component* sprite);
  void          remove_sprite(Sprite_Component* sprite);

  [[nodiscard]] float get_screen_width() const { return  d_screen_width; }
  [[nodiscard]] float get_screen_height() const { return d_screen_height; }

  Shared_Ref<Texture> get_texture(const std::string &file_name);

  static void begin_scene(Orthographic_Camera& camera);
  static void submit(const Shared_Ref<Shader>& shader, const Shared_Ref<Vertex_Array>& vertex_array);
  void static draw_indexed(const Shared_Ref<Vertex_Array>& vertex_array, uint32_t count = 0);

private:
  struct Scene_data{
    glm::mat4 d_view_project;
  };

  bool load_shaders();
  void create_verts();

  // map of textures loaded
  std::unordered_map<std::string, Shared_Ref<Texture>> d_textures;

  Shared_Ref<Shader>             d_shader;

 static Unique_ptr<Scene_data>   d_scene;
 Shared_Ref<Vertex_Array>        d_vertex_array;
 Shared_Ref<Vertex_Buffer>       d_vertex_buffer;

 Shared_Ref<Texture>             d_texture;
 Game*                           d_game;

  // all sprite component drawn
  std::vector<Sprite_Component*>    d_sprites;
  float                             d_screen_width {};
  float                             d_screen_height {};

  Ortho_camera_controller          d_camera;
  glm::mat4                        d_project;
  SDL_Window                       *d_window;
  SDL_GLContext                    d_context;

};

}
#endif// MY_GAME_RENDERER_H
