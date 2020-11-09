//
// Created by kuchlong2 on 7/26/20.
//

#ifndef MY_GAME_GAME_H
#define MY_GAME_GAME_H
#include <string>
#include <vector>
#include<unordered_map>
#include "util.h"

namespace my_game {
class  Actor;
class Renderer;
class Robot;
class Game
{
public:
        Game();
       ~Game();


  bool init();
  void run_loop();

  void shut_down();

  void add_actor(Actor* actor);
  void remove_actor(Actor *actor);

  [[nodiscard]] auto get_renderer()const{ return d_renderer.get();}

private:

  void process_input();
  void update();
  void generate_out_put();
  void load_data();
// robot actor
  Robot*                     d_robot;
  std::vector<Actor*>        d_actors;
  // pending actors
  std::vector<Actor*>        d_pending_actors;

  uint32_t                   d_ticks_count;
  bool                       d_is_running;
  std::unique_ptr<Renderer>  d_renderer;
  bool                       d_updating_actors;
};
}
#endif// MY_GAME_GAME_H
