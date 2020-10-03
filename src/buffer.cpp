#include "../include/buffer.h"
namespace my_game {

//==============================================================================
//===============Vertex_Buffer==================================================
//==============================================================================

Shared_Ref<Vertex_Buffer> Vertex_Buffer::create(uint32_t size) { return create_shared<Vertex_Buffer>(size); }

Shared_Ref<Vertex_Buffer> Vertex_Buffer::create(float *vertices, uint32_t size)
{
  return create_shared<Vertex_Buffer>(vertices, size);
}


Vertex_Buffer::Vertex_Buffer(uint32_t size)
{
  glGenBuffers(1, &d_renderID);
  glBindBuffer(GL_ARRAY_BUFFER, d_renderID);
  glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_DYNAMIC_DRAW);
}

Vertex_Buffer::Vertex_Buffer(float *vertices, uint32_t size)
{
  glGenBuffers(1, &d_renderID);
  glBindBuffer(GL_ARRAY_BUFFER, d_renderID);
  glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
}

Vertex_Buffer::~Vertex_Buffer() { glDeleteBuffers(1, &d_renderID); }


void Vertex_Buffer::bind() const { glBindBuffer(GL_ARRAY_BUFFER, d_renderID); }

void Vertex_Buffer::set_data(const void *data, uint32_t size)
{
  GLCall(glBindBuffer(GL_ARRAY_BUFFER, d_renderID));
  GLCall(glBufferSubData(GL_ARRAY_BUFFER, 0, size, data));
}
void Vertex_Buffer::un_bind() const {
  glBindBuffer(GL_ARRAY_BUFFER, 0);
}
//===============================================================
//===========  Index_Buffer  ====================================
//===============================================================

Index_Buffer::Index_Buffer(uint32_t *indices, uint32_t count)
{
  GLCall(glGenBuffers(1, &d_renderID));

  GLCall(glBindBuffer(GL_ARRAY_BUFFER, d_renderID));
  GLCall(glBufferData(GL_ARRAY_BUFFER, count * sizeof(uint32_t), indices, GL_STATIC_DRAW));
}
Index_Buffer::~Index_Buffer() { glDeleteBuffers(1, &d_renderID); }


void Index_Buffer::bind() const { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, d_renderID); }
void Index_Buffer::un_bind() const { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); }


Shared_Ref<Index_Buffer> Index_Buffer::create(uint32_t *indices, uint32_t size)
{
  return create_shared<Index_Buffer>(indices, size);
}

}