//
// Created by kuchlong2 on 7/26/20.
//

#include "../include/component.h"
#include "../include/actor.h"


namespace my_game{

Component::Component(Actor *owner, int update_order)
: d_owner{owner}
,d_update_order{update_order}
{
  d_owner->add_component(this);

}
Component::~Component()
{
  d_owner->remove_component(this);
}

void Component::update(float delta_time)
{}
void Component::process_input(const uint8_t* key_state) {}

}