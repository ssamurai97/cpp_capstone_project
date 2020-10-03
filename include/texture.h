//
// Created by kuchlong2 on 7/26/20.
//

#ifndef MY_GAME_TEXTURE_H
#define MY_GAME_TEXTURE_H
#include <string>
#include "util.h"
namespace my_game {

class Texture{
public:

  Texture(uint32_t width, uint32_t height);
  Texture() = default;
  ~Texture();
  bool load(const std::string& file_name);

  void bind(uint32_t slot = 0)const;
  void un_bind()const;

  bool operator ==(const Texture& rh) const{ return d_textureID == rh.d_textureID;}
 [[nodiscard]] uint32_t get_width()const{ return d_width; }
 [[nodiscard]] uint32_t get_height() const{ return  d_height; }
 [[nodiscard]] const std::string& get_file_name()const{return d_file_name;}
  void set_data(void* data, uint32_t size );

  [[nodiscard]] unsigned  int get_tex_ID()const{ return d_textureID;}
  static Shared_Ref<Texture> create(uint32_t width, uint32_t height);
  static Shared_Ref<Texture> create();
private:



  unsigned int d_textureID;
  std::string d_file_name;
  // image dimension in pixels
  uint32_t d_width {};
  uint32_t d_height{};
  unsigned char* d_data;
  GLenum   d_data_format;

    };
}

#endif// MY_GAME_TEXTURE_H
