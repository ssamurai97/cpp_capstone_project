//
// Created by kuchlong2 on 7/26/20.
//

#include "../include/actor.h"
#include "../include/game.h"
#include <algorithm>


namespace my_game{

Actor::Actor(Game *game)
:d_game{game}
,d_position{0.0f,0.0f}
, d_size{0.0f, 0.0f}
,d_recompute_world_transform{true}
,d_state{ACTIVE}

{
  d_game->add_actor(this);
}

Actor::~Actor()
{
  d_game->remove_actor(this);

  while (!d_components.empty()){
    delete d_components.back();
  }
}


void Actor::update_components(float delta_time)
{

  for(auto component : d_components){
    component->update(delta_time);
  }
}


void Actor::add_component(Component *component)
{
  auto order = component->get_update_order();
  auto itr = d_components.begin();
  for(;itr != d_components.end(); ++itr){
    if(order < (*itr)->get_update_order()){
      break;
    }
  }

  d_components.insert(itr,component);
}

void Actor::remove_component(Component *component)
{
  auto itr = std::find(std::begin(d_components), std::end(d_components), component);
  if(itr != d_components.end()){
    d_components.erase(itr);
  }
}
void Actor::update_actor(float delta_time) {}

void Actor::update(float delta_time) {

  if(d_state==ACTIVE) {
    compute_world_transform();
    update_components(delta_time);
    update_actor(delta_time);

    compute_world_transform();
  }
}
void Actor::compute_world_transform() {
  if(d_recompute_world_transform) {
    d_recompute_world_transform = false;


    d_world_transform = glm::translate(glm::mat4(1.0f),glm::vec3(d_position, 0.0f))
                        * glm::rotate(glm::mat4(1.0f), glm::radians(d_rotate), {0.0f, 0.0f, 1.0f})
                        * glm::scale(glm::mat4(1.0f),glm::vec3(d_size.x,d_size.y, 1.0f));


  }
}
void Actor::process_input(const uint8_t *key_state) {
  if(d_state==ACTIVE){
    for(auto cm : d_components){
      cm->process_input(key_state);
    }
    actor_input(key_state);
  }
}

}