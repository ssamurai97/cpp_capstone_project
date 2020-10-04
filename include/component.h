//
// Created by kuchlong2 on 7/26/20.
//

#ifndef MY_GAME_COMPONENT_H
#define MY_GAME_COMPONENT_H
#include <cstdint>
namespace my_game {
class Actor;
class Component
{
public:

  enum TypeID {
    COMPONENT = 0,
    CAMERA_COMPONENT,
    SPRITE_COMPONENT,
    NUM_COMPONENT_TYPES
  };

  Component(Actor* owner, int update_order = 100);
  virtual ~Component();

  virtual void update(float delta_time);
  virtual void process_input(const uint8_t* key_state);

  [[nodiscard]] Actor* get_owner()const {return d_owner;}
  [[nodiscard]] int get_update_order()const{ return d_update_order;}

  [[nodiscard]] virtual TypeID get_type()const = 0;

protected:
  // owner actor
  Actor* d_owner;
  //update order of the component
  int    d_update_order;

};
}
#endif// MY_GAME_COMPONENT_H
