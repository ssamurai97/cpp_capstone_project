//
// Created by kuchlong2 on 7/26/20.
//

#include "../include/game.h"
#include "../include/actor.h"
#include "../include/renderer.h"
#include <spdlog/spdlog.h>
#include <memory>
#include <algorithm>
namespace my_game{

Game::Game()
:d_ticks_count{0}
,d_is_running{true}
,d_renderer{ nullptr}
,d_updating_actors{false}
{}

Game::~Game()
{

}

bool Game::init()
{
  if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO) != 0)
  {
    spdlog::error("Unable to initialize SDL: %s", SDL_GetError());
    return false;
  }

  d_renderer = std::make_unique<Renderer>(this);

  d_renderer->init(1024, 786);

  load_data();

  d_ticks_count = SDL_GetTicks();
  return true;
}

void Game::run_loop()
{
  while (d_is_running){
    process_input();
    update();
    generate_out_put();
  }
}

void Game::update()
{
  while (!SDL_TICKS_PASSED(SDL_GetTicks(), d_ticks_count + 16))
    ;

  auto deltaTime = (SDL_GetTicks() - d_ticks_count) / 1000.0f;
  if (deltaTime > 0.05f)
  {
    deltaTime = 0.05f;
  }
  d_ticks_count = SDL_GetTicks();

  //update all actor
  d_updating_actors = true;
  for(auto actor : d_actors){
    actor->update(deltaTime);
  }
  d_updating_actors = false;
for(auto pending : d_pending_actors){
   pending->compute_world_transform();
  d_actors.emplace_back(pending);
}

d_pending_actors.clear();


std::vector<Actor*> dead_actors;
for(auto actor : d_actors){
  if(actor->get_state()==Actor::DEAD){
    dead_actors.emplace_back(actor);

  }
}
for(auto actor: dead_actors){
  delete actor;
}
}

void Game::generate_out_put()
{
  d_renderer->draw();

}

void Game::process_input()
{
SDL_Event event;
while (SDL_PollEvent(&event)) {
  if(event.type == SDL_QUIT) { d_is_running = false; }
}
  auto *state = SDL_GetKeyboardState(nullptr);
  if(state[SDL_SCANCODE_ESCAPE]){
    d_is_running = false;
  }


  d_updating_actors = true;
  for(auto actors : d_actors){
    actors->process_input(state);
  }
  d_updating_actors = false;
}
void Game::add_actor(Actor *actor) {
  if(d_updating_actors){
    d_pending_actors.emplace_back(actor);

  }else{
    d_actors.emplace_back(actor);
  }
}
void Game::remove_actor(Actor *actor) {
  //check in pending actors
  auto itr =  std::find(std::begin(d_pending_actors), std::end(d_pending_actors), actor);
  if(itr != d_pending_actors.end()){
    std::iter_swap(itr, d_pending_actors.end() -1 );
    d_pending_actors.pop_back();
  }

  itr = std::find(std::begin(d_actors), std::end(d_actors), actor);
  if(itr != d_actors.end()){
    std::iter_swap(itr, d_actors.end() -1);
    d_actors.pop_back();
  }
}
void Game::load_data() {

}
}