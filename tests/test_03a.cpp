#include <iostream>
#include <vector>
#include "Field.h"
#include "Obj_fabric.h"
#include "Obj_manager.h"
#include "Log_config.h"

#include "Chest.h"
#include "Reward.h"
#include "Trap.h"
#include "Entity.h"

int main() {
  SETUP_BASE_COLOR;
  std::cout << "\n=== test_03 (Obj_Fabric & Ecosystem Test) ===" << std::endl;
  ANCOLORING;

  std::cout << "\n--- Step 1: Spawning Objects via Fabric ---" << std::endl;
  
  Obj* chest  = FABRIC.create_object(FABRIC_TYPE::CHEST);
  Obj* coin   = FABRIC.create_object(FABRIC_TYPE::COIN);
  Obj* weapon = FABRIC.create_object(FABRIC_TYPE::WEAPON);
  Obj* spikes = FABRIC.create_object(FABRIC_TYPE::TRAP_SPIKES);
  Obj* skel   = FABRIC.create_object(FABRIC_TYPE::ENTITY_SKELETON);
  Obj* skel_p = FABRIC.create_object(FABRIC_TYPE::ENTITY_POTION);

  std::cout << "\n--- Step 2: Placing Objects on Field manually ---" << std::endl;
    
  FIELD.set_Obj(0, 0, chest);
  FIELD.set_Obj(0, 1, coin);
  FIELD.set_Obj(0, 2, weapon);
  FIELD.set_Obj(1, 0, spikes);
  FIELD.set_Obj(1, 1, skel);
  FIELD.set_Obj(1, 2, skel_p);

  std::cout << "\n--- Current Field State ---" << std::endl;
  FIELD.print_field();

  std::cout << "\n--- Step 3: Inspecting Randomly Generated Values ---" << std::endl;
   
  if (coin && coin->get_type() == OBJ_TYPE::REVARD) {
    Coin* c = dynamic_cast<Coin*>(coin);
    if (c && c->get_reward_type() == REWARD_TYPE::COIN) {
      std::cout << "[Test Log] Coin gold amount generated: " << c->get_gold_amount() << std::endl;
    }
  }

  if (weapon && weapon->get_type() == OBJ_TYPE::REVARD) {
    Weapon* w = dynamic_cast<Weapon*>(weapon);
    if (w && w->get_reward_type() == REWARD_TYPE::WEAPON) {
      std::cout << "[Test Log] Weapon damage: " << w->get_damage_performance() 
                << " | Element type ID: " << int(w->get_elemental_type()) << std::endl;
    }
  }

  if (spikes && spikes->get_type() == OBJ_TYPE::TRAP) {
    Spikes* s = dynamic_cast<Spikes*>(spikes);
    if (s) { 
       std::cout << "[Test Log] Spikes damage: " << s->get_spikes_damage() 
                 << " | Active now: " << (s->get_active_status() ? "YES" : "NO") << std::endl;
    }
  }

  std::cout << "\n--- Step 4: Simulating Turn with Obj_manager ---" << std::endl;
   
  OBJ_MGR.tick_all_eff();
    
  if (spikes && spikes->get_type() == OBJ_TYPE::TRAP) {
    Spikes* s = dynamic_cast<Spikes*>(spikes);
    if (s) {
      std::cout << "[Test Log] Spikes active after 1 tick: " << (s->get_active_status() ? "YES" : "NO") << std::endl;
    }
  }

  std::cout << "\n--- Step 5: Cleaning up whole field ---" << std::endl;
  
  OBJ_MGR.clear_field();
  
  std::cout << "\n--- Field State After Wipe ---" << std::endl;
  FIELD.print_field();

  std::cout << "\n=== Test 03 Finished Successfully ===" << std::endl;
  return 0;
}
