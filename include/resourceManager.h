//
// Created by kuchlong2 on 9/17/20.
//

#ifndef MY_GAME_RESOURCEMANAGER_H
#define MY_GAME_RESOURCEMANAGER_H
#include <map>
#include <string>
#include "util.h"
namespace my_game {
class Shader;
class Texture;
class Resource_manager
{
public:

  Resource_manager() = delete;
  // resource storage
  static std::map<std::string, Shared_Ref<Shader>> Shaders;
  static std::map<std::string, Shared_Ref<Texture>> Textures;

  static void  add_shader(const std::string& name, const Shared_Ref<Shader>& shader);
  static void  add_shader(const Shared_Ref<Shader>& shader);
  static Shared_Ref<Shader> get_shader(const std::string&  name);

  static Shared_Ref<Texture> add_texture(const std::string& name, const std::string& file);
  // retrieves a stored texture
  static Shared_Ref<Texture> get_texture(const std::string& name);

  [[nodiscard]] static bool shader_exist(const std::string& name){
    return Shaders.find(name)!= Shaders.end();
  }

  static bool tex_exist(const std::string& name){
    return Textures.find(name) != Textures.end();
  }

  // loads and generates a shader from file
  static Shared_Ref<Shader> load_shader(const std::string& name,const std::string& file);
private:
  static Shared_Ref<Shader> load_shader(const std::string& file);
  // loads a single texture from file
  static Shared_Ref<Texture> load_texture(const std::string& file);
};
}

#endif//
