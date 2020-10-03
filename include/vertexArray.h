
#ifndef MY_GAME_VERTEX_ARRAY_H
#define MY_GAME_VERTEX_ARRAY_H
#include "buffer.h"

namespace my_game {

class Vertex_Array
{
public:
  //constructors
  Vertex_Array();
  ~Vertex_Array();


  //accessors/methods
  void bind()const;
  void un_bind()const;

  void add_vertex_buffer(const Shared_Ref<Vertex_Buffer> &vertex_buffer);
  void set_index_buffer(const Shared_Ref<Index_Buffer>& index_buffer);

  [[nodiscard]] const std::vector<Shared_Ref<Vertex_Buffer>>& get_vertex_buffer()const{
    return d_vertex_buffer;
  }

  [[nodiscard]] const Shared_Ref<Index_Buffer>& get_index_buffer()const{ return d_index_buffer;}

  static Shared_Ref<Vertex_Array> create();

private:
  uint32_t d_renderID;
  uint32_t d_vertex_buffer_index{0};
  std::vector<Shared_Ref<Vertex_Buffer>> d_vertex_buffer;
  Shared_Ref<Index_Buffer> d_index_buffer;

};
}

#endif//
