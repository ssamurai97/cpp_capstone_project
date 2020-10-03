//
// Created by kuchlong2 on 7/26/20.
//

#include "../include/texture.h"
#include <GL/glew.h>
#include <spdlog/spdlog.h>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

 namespace my_game{
  Texture::Texture(uint32_t width , uint32_t height ) : d_textureID{ 0 }, d_width{width}, d_height{ height }
  ,d_data{ nullptr}
 {}


  Texture::~Texture() { glDeleteTextures(1, &d_textureID); }



  bool Texture::load(const std::string &file_name)
  {
    int chan{ 0 };
    int width, height;
    stbi_set_flip_vertically_on_load(1);

    d_data = stbi_load(file_name.c_str(), &width, &height, &chan, 0);
    if (d_data == nullptr) {
      spdlog::error(" STBI failed to load image {} ", file_name.c_str());
      return false;
    }

    d_width = width;
    d_height = height;
    int format {GL_RGB};
    if (chan == 4) {
      format = GL_RGBA;
    }

    glGenTextures(1, &d_textureID);
    glBindTexture(GL_TEXTURE_2D, d_textureID);

    GLCall(glTexImage2D(GL_TEXTURE_2D, 0, format, d_width, d_height, 0, format, GL_UNSIGNED_BYTE,d_data ));

    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));

    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));


    stbi_image_free(d_data);
    return true;
  }


  void Texture::bind(uint32_t slot) const{
    GLCall(glActiveTexture(GL_TEXTURE0 + slot));
    GLCall(glBindTexture(GL_TEXTURE_2D, d_textureID));
  }


  Shared_Ref<Texture> Texture::create(uint32_t width, uint32_t height) { return create_shared<Texture>(width, height); }

  Shared_Ref<Texture> Texture::create() {
    return create_shared<Texture>(); }

void Texture::un_bind() const
  {
    glDeleteTextures(1,&d_textureID);
  }

  void Texture::set_data(void *data, uint32_t size)
  {
    glBindTexture(GL_TEXTURE_2D, d_textureID);
    glTexSubImage2D(d_textureID, 0, 0,0, d_width, d_height, d_data_format, GL_UNSIGNED_BYTE, data);

  }
  }