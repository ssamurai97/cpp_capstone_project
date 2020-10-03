//
// Created by kuchlong2 on 7/26/20.
//

#include "../include/vertexArray.h"
namespace my_game{

static GLenum shader_Data_Type_To_OpenGl_Type(Shader_Data_Type type){
  switch (type) {
  case Shader_Data_Type::Float:   return GL_FLOAT;
  case Shader_Data_Type::Float2:  return GL_FLOAT;
  case Shader_Data_Type::Float3:  return GL_FLOAT;
  case Shader_Data_Type::Float4:  return GL_FLOAT;
  case Shader_Data_Type::Mat3:    return GL_FLOAT;
  case Shader_Data_Type::Mat4:    return GL_FLOAT;
  case Shader_Data_Type::Int:     return GL_INT;
  case Shader_Data_Type::Int2:    return GL_INT;
  case Shader_Data_Type::Int3:    return GL_INT;
  case Shader_Data_Type::Int4:    return GL_INT;
  case Shader_Data_Type::Bool:    return GL_BOOL;
  case Shader_Data_Type::None:
    break;
  }
  return 0;
}

Vertex_Array::Vertex_Array()
{
  GLCall(glGenVertexArrays(1, &d_renderID));

}

Vertex_Array::~Vertex_Array()
{
  glDeleteVertexArrays(1, &d_renderID);
}

void Vertex_Array::bind()const{
  glBindVertexArray(d_renderID);
}

void Vertex_Array::un_bind() const
{
  glBindVertexArray(0);
}
Shared_Ref<Vertex_Array> Vertex_Array::create()
{
  return create_shared<Vertex_Array>();
}

void Vertex_Array::add_vertex_buffer(const Shared_Ref<Vertex_Buffer> &vertex_buffer)
{
  GLCall(glBindVertexArray(d_renderID));

  vertex_buffer->bind();
  const auto& layout = vertex_buffer->get_layout();
  for(const auto& element : layout){
    switch (element.Type) {
    case Shader_Data_Type::Float:
    case Shader_Data_Type::Float2:
    case Shader_Data_Type::Float3:
    case Shader_Data_Type::Float4:
    case Shader_Data_Type::Int:
    case Shader_Data_Type::Int2:
    case Shader_Data_Type::Int3:
    case Shader_Data_Type::Int4:
    case Shader_Data_Type::Bool:
    {
      GLCall(glEnableVertexAttribArray(d_vertex_buffer_index));
      glVertexAttribPointer(d_vertex_buffer_index,
        element.get_component(),
        shader_Data_Type_To_OpenGl_Type(element.Type),
        element.Normalized ? GL_TRUE : GL_FALSE,
        layout.get_stride(),
                            (const void*)element.Offset);
      d_vertex_buffer_index++;
      break;
    }
    case Shader_Data_Type::Mat3:
    case Shader_Data_Type::Mat4:
    {
      uint8_t count = element.get_component();
      for(uint8_t i {0}; i < count; ++i){
        GLCall(glEnableVertexAttribArray(d_vertex_buffer_index));
        GLCall(glVertexAttribPointer(d_vertex_buffer_index,
          count,
          shader_Data_Type_To_OpenGl_Type(element.Type),
          element.Normalized ? GL_TRUE : GL_FALSE,
          layout.get_stride(),
                              (const void*)(sizeof(float) * count * i)));
        d_vertex_buffer_index++;
      }
      break;
    }
    default:
      fmt::print("unknown Shader_data_type");
    }
  }
  d_vertex_buffer.push_back(vertex_buffer);
}

void Vertex_Array::set_index_buffer(const Shared_Ref<Index_Buffer> &index_buffer)
{
  GLCall(glBindVertexArray(d_renderID));

  index_buffer->bind();

  d_index_buffer = index_buffer;
}

}
