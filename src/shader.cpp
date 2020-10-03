//
// Created by kuchlong2 on 7/26/20.
//

#include "../include/shader.h"
#include <fstream>
#include <sstream>
#include <spdlog/spdlog.h>
#include <array>
#include <glm/gtc/type_ptr.hpp>
#include <utility>
namespace my_game{
static GLenum Shader_type(const std::string& type){
  if (type == "vertex")
    return GL_VERTEX_SHADER;
  if (type == "fragment" || type == "pixel")
    return GL_FRAGMENT_SHADER;
  else
    fmt::print("unknown type ");
  return 0;
}

Shader::Shader(const std::string &filepath){
  std::string source = read_file(filepath);
  auto shader_sources = process_shader(source);
  if(!compile_shader(shader_sources)){
    spdlog::error("failed to compiled shader");
  }

  // Extract name from filepath
  auto last_slash = filepath.find_last_of("/\\");
  last_slash = last_slash == std::string::npos ? 0 : last_slash + 1;
  auto last_dot = filepath.rfind('.');
  auto count = last_dot == std::string::npos ? filepath.size() - last_slash : last_dot - last_slash;
  d_name = filepath.substr(last_slash, count);

}

Shader::Shader(std::string name, const std::string &vertex_src, const std::string &fragment_src)
:d_name{std::move(name)}{

  std::unordered_map<GLenum, std::string> src;
  src[GL_VERTEX_SHADER] = vertex_src;
  src[GL_FRAGMENT_SHADER] = fragment_src;
  compile_shader(src);
}

Shader::~Shader()noexcept{
  glDeleteProgram(d_renderID);
}

void Shader::set_uniform1f(const std::string &name, float value) {
  GLCall(glUniform1f(get_uniform_location(name), value));
}

void Shader::set_uniform1i(const std::string &name, int value) {
  GLCall(glUniform1i(get_uniform_location(name), value));
}

void Shader::set_floatUniform(const char *name, float value) {
  GLCall(glUniform1f(get_uniform_location(name), value));
}


 void Shader::set_uniform_4f(const std::string &name, const glm::vec4& value) {
  GLCall(glUniform4f(get_uniform_location(name),value.x, value.y, value.z, value.w));
}

void Shader::set_uniform_array(const std::string& name, int* values, uint32_t count){

  GLCall(glUniform1iv(get_uniform_location(name), count, values));
}

int Shader::get_uniform_location(const std::string &name) const {
  if(d_uniform_catch.find(name) != d_uniform_catch.end())
    return d_uniform_catch[name];
  GLCall(int loc =  glGetUniformLocation(d_renderID, name.c_str()));
  if(loc == -1)
    spdlog::error("Warning uniform {} does not exists", name);


  d_uniform_catch[name] = loc;
  return loc;
}

void Shader::set_uniform_mat4f(const std::string &name, const glm::mat4 &matrix) {

  GLCall(glUniformMatrix4fv(get_uniform_location(name),1, GL_FALSE,glm::value_ptr(matrix)));
}


void Shader::bind() const {
  glUseProgram(d_renderID);
}

void Shader::un_bind() const {
  glUseProgram(0);
}
Shared_Ref<Shader> Shader::create(const std::string& file_name) { return create_shared<Shader>(file_name); }
Shared_Ref<Shader> Shader::create(const std::string &name, const std::string &vertex_src, const std::string &fragment_src)
{
  return create_shared<Shader>(name, vertex_src, fragment_src);
}


bool Shader::compile_shader(const std::unordered_map<GLenum , std::string> &shader_sources) {
  auto program = glCreateProgram();

  std::array<GLenum, 2>gl_shaderID {};
  auto shader_indexID = 0;
  for(auto&[ first, second] : shader_sources){
    GLenum type = first;
    const std::string& source = second;
    auto shader = glCreateShader(type);

    auto *source_cstr = source.c_str();

    GLCall(glShaderSource(shader, 1, &source_cstr, nullptr));

    GLCall(glCompileShader(shader));

    if(!is_compiled(shader)){
      spdlog::error("failed to compiled shader{} \n");
      return false;
    }
    GLCall(glAttachShader(program, shader));

    gl_shaderID[shader_indexID++] = shader;
  }

  d_renderID = program;

  GLCall(glLinkProgram(program));
  if(!is_valid_program(program, gl_shaderID)){
    spdlog::error("failed to link shader!");
    return false;
  }

  for(auto id : gl_shaderID){
    glDetachShader(program, id);
    glDeleteShader(id);
  }

  return true;
  }
bool Shader::is_compiled(GLuint shader ) {
  GLint isCompiled = 0;
  glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
  if (isCompiled == GL_FALSE)
  {
    GLint maxLength = 0;
    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

    std::vector<GLchar> infoLog(maxLength);
    glGetShaderInfoLog(shader, maxLength, &maxLength, &infoLog[0]);

    glDeleteShader(shader);

    spdlog::error(" failed to link program {}", infoLog.data());
    return false;
  }

  return  true;

}

bool Shader::is_valid_program(GLuint program, std::array<GLenum, 2>gl_shaderID) const {

auto glShader = gl_shaderID;
  GLint isLinked = 0;
  glGetProgramiv(program, GL_LINK_STATUS, (int*)&isLinked);
  if (isLinked == GL_FALSE)
  {
    GLint maxLength = 0;
    glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

    // The maxLength includes the NULL character
    std::vector<GLchar> infoLog(maxLength);
    glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);

    // We don't need the program anymore.
    glDeleteProgram(program);

    for (auto id : glShader)
      glDeleteShader(id);

    spdlog::error(" {}", infoLog.data());
    return  false;
  }

  return true;
}


std::string Shader::read_file(const std::string& path){
  std::string result;
  std::ifstream in(path, std::ios::in | std::ios::binary); // ifstream closes itself due to RAII
  if (in)
  {
    in.seekg(0, std::ios::end);
    size_t size = in.tellg();
    if (size != -1)
    {
      result.resize(size);
      in.seekg(0, std::ios::beg);
      in.read(&result[0], size);
    }
    else
    {
      spdlog::error("Could not read from file '{}'", path);
    }
  }
  else
  {
    spdlog::error("Could not open file '{0}'", path);
  }

  return result;
}
std::unordered_map<GLenum, std::string> Shader::process_shader(const std::string &file)
{

  std::unordered_map<GLenum, std::string> shader_sources;

  const char* type_token = "#type";
  size_t type_token_length = strlen(type_token);
  size_t pos = file.find(type_token, 0); //Start of shader type declaration line
  while (pos != std::string::npos)
  {
    size_t eol = file.find_first_of("\r\n", pos); //End of shader type declaration line

    size_t begin = pos + type_token_length + 1; //Start of shader type name (after "#type " keyword)
    std::string type = file.substr(begin, eol - begin);

    size_t nextLinePos = file.find_first_not_of("\r\n", eol); //Start of shader code after shader type declaration line

    pos = file.find(type_token, nextLinePos); //Start of next shader type declaration line

    shader_sources[Shader_type(type)] = (pos == std::string::npos) ? file.substr(nextLinePos) : file.substr(nextLinePos, pos - nextLinePos);
  }

  return shader_sources;
}


}