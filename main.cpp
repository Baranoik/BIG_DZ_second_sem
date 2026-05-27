#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include "Field.h"
#include "input.h"
#include "Interaction_sys.h"
#include "Obj_manager.h"
#include "Obj_fabric.h"
#include "objects/Player.h"
#include "Render.h"
#include "Log_config.h"

int main() {
  sf::RenderWindow window(sf::VideoMode({600, 600}), "Turn-Based Roguelike Game");
  window.setFramerateLimit(60);

  if (!RENDER.init("Front.ttf")) {
      std::cout << "ERROR :: Не удалось загрузить шрифт!" << std::endl;
      return -1;
  }

  Player* player = new Player();
  std::vector<Obj*> start_objects;
  start_objects.push_back(player);                                
  start_objects.push_back(FABRIC.create_object(FABRIC_TYPE::CHEST)); 
  start_objects.push_back(FABRIC.create_random_reward());         
  start_objects.push_back(nullptr);                              
  start_objects.push_back(nullptr);                              
    
  for (int i = 0; i < 4; ++i) {
    start_objects.push_back(FABRIC.create_random_entity());
  }

  std::random_device rd;
  std::default_random_engine urng(rd());
  std::shuffle(start_objects.begin(), start_objects.end(), urng);

  int obj_index = 0;
  for (int x = 0; x < GRID_SIZE_X; ++x) {
    for (int y = 0; y < GRID_SIZE_Y; ++y) {
      if (start_objects[obj_index] != nullptr) {
        FIELD.set_Obj(x, y, start_objects[obj_index]);
      }
      obj_index++;
    }
  }
  Key_input input_sys;
  int p_x = 0;
  int p_y = 0;
  int dx = 0;
  int dy = 0;

  std::cout << "Генерация завершена!" << std::endl;
  FIELD.print_field();
  bool spawn = true;
  while (window.isOpen()) {
    Command cmd = input_sys.get_input(window);
    bool step_triggered = (cmd != Command::NONE);
      
    dx = 0;
    dy = 0;

    if (cmd == Command::MOVE_UP)    dx = -1;
    if (cmd == Command::MOVE_DOWN)  dx = 1;
    if (cmd == Command::MOVE_LEFT)  dy = -1;
    if (cmd == Command::MOVE_RIGHT) dy = 1;

    if (step_triggered && !player->isdead()) {
      for (int x = 0; x < GRID_SIZE_X; ++x) {
        for (int y = 0; y < GRID_SIZE_Y; ++y) {
          if (FIELD.get_Obj(x, y) == player) {
            p_x = x;
            p_y = y;
          }
        }
      }

      int target_x = p_x + dx;
      int target_y = p_y + dy;

      LOG("=== НАЧАЛО ПОШАГОВОГО ХОДА ===");

      spawn = !spawn;
      INTERACT.process_step(player, p_x, p_y, target_x, target_y);
      OBJ_MGR.tick_all_eff();
      OBJ_MGR.cleanup_dead_objects();
      if (spawn){
        OBJ_MGR.check_and_refill_field();
      }
      LOG("Текущие счетчики -> Врагов: " << OBJ_MGR.count_objects_by_type(OBJ_TYPE::ENTITY));
      FIELD.print_field();
      player->lv_up();
        LOG("=== КОНЕЦ ПОШАГОВОГО ХОДА ===");
      }

      window.clear(sf::Color::Black); 

      bool player_alive = false;
      for (int x = 0; x < GRID_SIZE_X; ++x) {
        for (int y = 0; y < GRID_SIZE_Y; ++y) {
          if (FIELD.get_Obj(x, y) == player) {
            player_alive = true;
          }
        }
      }

      if (player_alive && !player->isdead()) {
        RENDER.draw_all(window, player);
      } else {
        RENDER.draw_all(window, nullptr);
      }

      window.display(); 
  }

  OBJ_MGR.clear_field();
  return 0;
}
