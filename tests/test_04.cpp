#include <iostream>
#include "Field.h"
#include "Player.h"
#include "Entity.h"
#include "Reward.h"
#include "Chest.h"
#include "Interaction_sys.h"
#include "Obj_manager.h"
#include "Log_config.h"

void end_of_turn() {
  OBJ_MGR.tick_all_eff();
  OBJ_MGR.cleanup_dead_objects();
  FIELD.print_field();
}

int main() {
  SETUP_BASE_COLOR;
  std::cout << "\n=== Test 04: Pure Interaction System & Combat Test ===\n" << std::endl;
  ANCOLORING;

  Player* player = new Player();
  FIELD.set_Obj(1, 1, player); // Игрок на {1;1}
    
  std::cout << "\n--- Scenario 1: Combat WITH Weapon ---" << std::endl;
  Skeleton* weak_skel = new Skeleton();
  weak_skel->set_soundness(5); 
  FIELD.set_Obj(0, 1, weak_skel); // Скелет СВЕРХУ {0;1}

  std::cout << "Initial Weapon Perf: " << player->get_weapon_damage() << std::endl;
  FIELD.print_field();

  INTERACT.process_step(player, 1, 1, 0, 1);
  end_of_turn();

  std::cout << "\nResult Scenario 1:" << std::endl;
  std::cout << "Weapon Perf after fight (expected 11 - 5 = 6): " << player->get_weapon_damage() << std::endl;
  std::cout << "Player Position (expected to stay at {1;1} due to weapon combat rule):" << std::endl;


  std::cout << "\n--- Scenario 2: Combat WITHOUT Weapon (Bare Hands) ---" << std::endl;
  player->damage_weapon(player->get_weapon_damage()); 
  std::cout << "Weapon Perf now: " << player->get_weapon_damage() << " (Hands Mode ACTIVE)" << std::endl;

  Skeleton* hand_skel = new Skeleton();
  hand_skel->set_soundness(4); 
  FIELD.set_Obj(0, 1, hand_skel);
  FIELD.print_field();

  INTERACT.process_step(player, 1, 1, 0, 1);
  end_of_turn();

  std::cout << "\nResult Scenario 2:" << std::endl;
  std::cout << "Player HP after fight (expected 10 - 4 = 6): " << player->get_hp() << std::endl;
  std::cout << "Player Position (expected to step on {0;1} automatically, no loot):" << std::endl;


  std::cout << "\n--- Scenario 3: Stepping on a Potion (Reward) ---" << std::endl;
  Potion* test_potion = new Potion(ELEMENT_TYPE::FIRE);
  FIELD.set_Obj(0, 2, test_potion);
  FIELD.print_field();

  INTERACT.process_step(player, 0, 1, 0, 2);
  end_of_turn();

  std::cout << "\nResult Scenario 3:" << std::endl;
  std::cout << "Player Position (expected to absorb potion and step on cell {0;2}):" << std::endl;


  std::cout << "\n--- Scenario 4: Hit a Chest ---" << std::endl;
  Chest* test_chest = new Chest();
  FIELD.set_Obj(1, 2, test_chest);
  FIELD.print_field();

  INTERACT.process_step(player, 0, 2, 1, 2);
  end_of_turn();

  std::cout << "\nResult Scenario 4:" << std::endl;
  std::cout << "Player Position (expected to stay on {0;2}, chest replaced by reward on {1;2}):" << std::endl;

  OBJ_MGR.clear_field();
  std::cout << "\n=== Test 04 Finished Successfully ===" << std::endl;
  return 0;
}
