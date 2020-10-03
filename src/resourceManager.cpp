//
// Created by kuchlong2 on 9/17/20.
//

#include "../include/resourceManager.h"
#include "../include/shader.h"
#include "../include/texture.h"
namespace my_game{

std::map<std::string, Shared_Ref<Shader>> Resource_manager::Shaders;
std::map<std::string, Shared_Ref<Texture>> Resource_manager::Textures;

Shared_Ref<Shader> Resource_manager::load_shader(const std::string &name, const std::string &file)
{
  auto shader = Shader::create(file);
  add_shader(name, shader);
  return shader;
}

void Resource_manager::add_shader(const std::string& name, const Shared_Ref<Shader>& shader)
{
  if(!shader_exist(name)){
    fmt::print("shader exist already");
  }
  Shaders[name] = shader;
}
Shared_Ref<Shader> Resource_manager::get_shader(const std::string &name)
{
  if(!shader_exist(name)){
    fmt::print("shader doesn't exist", shader_exist(name));
  }
  return Shaders[name];
}

Shared_Ref<Texture> Resource_manager::add_texture(const std::string &name, const std::string& file)

  { Textures[name] = load_texture(file);

    return Textures[name];
  }

  Shared_Ref<Texture> Resource_manager::get_texture(const std::string &name)
  {
    if(!tex_exist(name)) { fmt::print("texture not found: {} ", tex_exist(name)); }
    return Textures[name];
  }


Shared_Ref<Texture> Resource_manager::load_texture(const std::string &file)
{
  auto texture = Texture::create();
  texture->load(file);
  return texture;
}
Shared_Ref<Shader> Resource_manager::load_shader(const std::string &file) {
  auto shader = Shader::create(file);
  add_shader(shader);
  return shader;
}

void Resource_manager::add_shader(const Shared_Ref<Shader>& shader)
{

  auto& name = shader->get_name();
  add_shader(name, shader);

}

}