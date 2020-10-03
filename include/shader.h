//
// Created by kuchlong2 on 7/26/20.
//

#ifndef MY_GAME_SHADER_H
#define MY_GAME_SHADER_H
#include "util.h"
#include <string>
#include <unordered_map>
#include <glm/glm.hpp>

namespace my_game {


// Class representing a shader, i.e. a compiled GLSL program that the GPU uses
// in order to draw something
class Shader
{
public:

  explicit Shader(const std::string &filepath);
  Shader(std::string  name, const std::string& vertex_src, const std::string& fragment_src);
  ~Shader() noexcept;

  void bind() const;
  void un_bind() const;

  // Sets a float uniform
  void set_floatUniform(const char *name, float value);
  void set_uniform_4f(const std::string &name, const glm::vec4& value);

  void set_uniform1f(const std::string &name, float v);
  void set_uniform1i(const std::string &name, int v);

  void set_uniform_mat4f(const std::string &name, const glm::mat4 &matrix);

  const std::string& get_name()const{ return d_name;}
  void set_uniform_array(const std::string& name, int* values, uint32_t count);

  static Shared_Ref<Shader>  create(const std::string& file_name);
  static Shared_Ref<Shader>  create(const std::string& name, const std::string& vertex_src, const std::string& fragment_src);
private:
  // Tries to compile the specified shader
  bool compile_shader(const std::unordered_map<unsigned int, std::string>& sources);


  //check if vertex / fragment program link
  bool is_valid_program(GLuint program, std::array<GLenum, 2>glshaderID) const;

  // get uniform location
  int get_uniform_location(const std::string &name) const;
  static std::string read_file(const std::string& path);

  // parse shader file
  static std::unordered_map<GLenum, std::string> process_shader(const std::string& file);
  // check if compiled shader is successful
  bool is_compiled(GLuint shader);
private:
  // Store the shader object IDs
  unsigned int d_renderID;
  std::string  d_name;
  mutable std::unordered_map<std::string, int> d_uniform_catch;
};

}
#endif// MY_GAME_SHADER_H
