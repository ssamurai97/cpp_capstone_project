//
// Created by kuchlong2 on 7/26/20.
//

#ifndef MY_GAME_ACTOR_H
#define MY_GAME_ACTOR_H
#include <cstdint>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "component.h"
namespace my_game {
class Game;

class Actor
{
public:

   enum class TypeID{
    ACTOR = 0,
    NUM_ACTOR_TYPES
  };

  static const char* TypeNames[static_cast<int>(TypeID::NUM_ACTOR_TYPES)];
  enum State
  {
    ACTIVE,
    PAUSED,
    DEAD
  };

   explicit Actor(Game *game);

   virtual ~Actor();

   void update(float delta);

   void update_components(float  delta_time);

   virtual void update_actor(float delta_time);

   void process_input(const uint8_t* key_state);
   virtual void actor_input(const uint8_t* key_state) {}
   void compute_world_transform();


  [[nodiscard]] const glm::mat4& get_world_transform()const{ return d_world_transform;}
  [[nodiscard]] glm::vec2 get_forward()const{ return glm::vec2(glm::cos(d_rotate),glm::sin(d_rotate));}

  [[nodiscard]] float get_rotation()const{ return d_rotate;}

  [[nodiscard]] glm::vec2 get_position()const { return d_position;}

  [[nodiscard]] State get_state()const{ return d_state;}

  [[nodiscard]] glm::vec2 get_size()const{ return  d_size;}

  [[nodiscard]] virtual TypeID get_type()const { return TypeID::ACTOR;}

  [[nodiscard]] const std::vector<Component*>& get_components()const { return d_components; }
 void set_rotation(float rotate){d_rotate = rotate; d_recompute_world_transform= true;}
 void set_position(const glm::vec2& pos){d_position = pos; d_recompute_world_transform = true; }

 void set_state(State state){ d_state = state; }
 void set_size(const glm::vec2& size){ d_size = size; d_recompute_world_transform = true;}


  Game* get_game(){ return d_game; }
  //add component
  void add_component(Component* component);
 // remove component
  void remove_component(Component* component);


   Component* get_component_type(Component::TypeID type){
   Component* component {nullptr};

   for(Component* c : d_components){
    if(c->get_type() == type){
      component = c;
      break;
     }
   }
   return component;
  }

private:

   State                   d_state;
   glm::mat4               d_world_transform = glm::mat4();

   glm::vec2                d_position;
   glm::vec2                d_size{};
   float                    d_rotate{};
   bool                     d_recompute_world_transform;
   std::vector<Component*>  d_components;
   Game                     *d_game;
};

}
#endif// MY_GAME_ACTOR_H
