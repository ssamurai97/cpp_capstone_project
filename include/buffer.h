//
// Created by kuchlong2
//
#ifndef MY_GAME_BUFFER_H
#define MY_GAME_BUFFER_H
#include <cstdint>
#include  <string>
#include <utility>
#include <vector>
#include "util.h"
namespace my_game{

//OpenGL Shader Type
enum class Shader_Data_Type {
  None = 0, Float, Float2,Float3, Float4, Mat3, Mat4, Int, Int2, Int3, Int4, Bool
};

static uint32_t Shader_data_type_size(Shader_Data_Type type){
  switch (type) {
  case Shader_Data_Type::Float:   return 4;
  case Shader_Data_Type::Float2:  return 4 * 2;
  case Shader_Data_Type::Float3:  return 4 * 3;
  case Shader_Data_Type::Float4:  return 4 * 4;
  case Shader_Data_Type::Mat3:    return 4 * 3 * 3;
  case Shader_Data_Type::Mat4:    return 4 * 4 * 4;
  case Shader_Data_Type::Int:     return 4;
  case Shader_Data_Type::Int2:    return 4 *2;
  case Shader_Data_Type::Int3:    return 4 * 3;
  case Shader_Data_Type::Int4:    return 4 * 4;
  case Shader_Data_Type::Bool:    return 1;
  case Shader_Data_Type::None:
    break;
  }
  return 0;
}


struct Buffer_Element
{
  std::string Name;
  Shader_Data_Type Type;
  uint32_t Size{};
  std::size_t Offset{};
  bool Normalized{};
  Buffer_Element() = default;
  Buffer_Element(Shader_Data_Type type, std::string  name, bool normalized = false)
    :Type{ type }, Name{std::move(name)}, Size{ Shader_data_type_size(type) }, Offset{ 0 }, Normalized{ normalized }
  {}

  [[nodiscard]] uint32_t get_component() const
  {
    switch (Type) {
    case Shader_Data_Type::Float:
      return 1;
    case Shader_Data_Type::Float2:
      return 2;
    case Shader_Data_Type::Float3:
      return 3;
    case Shader_Data_Type::Float4:
      return 4;
    case Shader_Data_Type::Mat3:
      return 3;
    case Shader_Data_Type::Mat4:
      return 4;
    case Shader_Data_Type::Int:
      return 1;
    case Shader_Data_Type::Int2:
      return 2;
    case Shader_Data_Type::Int3:
      return 3;
    case Shader_Data_Type::Int4:
      return 4;
    case Shader_Data_Type::Bool:
      return 1;
    case Shader_Data_Type::None:
      break;
    }
    return 0;
  }

};
// this class represent OpenGL Buffer layout
  class Buffer_Layout{
  public:

    Buffer_Layout() = default;

    Buffer_Layout(const std::initializer_list<Buffer_Element>& elements)
      :d_elements{elements}{  calculate_offset_and_stride();}

    [[nodiscard]] const std::vector<Buffer_Element>& get_elements()const {return d_elements;}

      std::vector<Buffer_Element>::iterator begin()      { return d_elements.begin(); }
      std::vector<Buffer_Element>::iterator end  ()      { return d_elements.end();   }
     [[nodiscard]]  std::vector<Buffer_Element>::const_iterator begin()const { return d_elements.begin(); }
     [[nodiscard]] std::vector<Buffer_Element>::const_iterator  end  ()const { return d_elements.end();   }

     [[nodiscard]] uint32_t get_stride()const { return d_stride;}
      private:
      void calculate_offset_and_stride(){
        std::size_t offset {0};
        d_stride = 0;
        for(auto& element : d_elements){
          element.Offset = offset;
          offset += element.Size;
          d_stride += element.Size;
        }
    }
      private:
    std::vector<Buffer_Element> d_elements;
    uint32_t d_stride {0};
  };

//  OpenGl Vertex buffer object
  class Vertex_Buffer
  {
  public:
    explicit Vertex_Buffer(uint32_t size);
    Vertex_Buffer(float* vertices, uint32_t size);

    ~Vertex_Buffer();
    void bind()const;
    void un_bind()const;

    void set_data(const void* data, uint32_t size );

    [[nodiscard]] const Buffer_Layout& get_layout()const { return d_layout;}

    void set_layout(const Buffer_Layout& layout){ d_layout = layout;};

    static Shared_Ref<Vertex_Buffer> create(uint32_t size);
    static Shared_Ref<Vertex_Buffer> create(float* vertices, uint32_t size);

  private:
    uint32_t d_renderID;
    Buffer_Layout d_layout;


  };


//Index buffer object 
  class Index_Buffer
  {
  public:

    Index_Buffer(uint32_t* indices, uint32_t count);
    ~Index_Buffer();
    void bind()const;
    void un_bind()const;

    [[nodiscard]] uint32_t get_count() const{ return d_count; }

    static Shared_Ref<Index_Buffer> create(uint32_t* indices, uint32_t count);

  private:
    uint32_t d_renderID;
    uint32_t d_count;
  };


}
#endif// MY_GAME_BUFFER_H
