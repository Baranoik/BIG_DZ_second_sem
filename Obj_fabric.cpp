#include "Obj_fabric.h"
#include "Log_config.h"
#include <random> 

Obj_Fabric& Obj_Fabric::get_instance() {
  static Obj_Fabric instance;
  return instance;
}

Obj* Obj_Fabric::create_object(FABRIC_TYPE type) {
  Obj* new_obj = nullptr;

  switch (type) {
    case FABRIC_TYPE::CHEST:             new_obj = new Chest(); break;
    case FABRIC_TYPE::COIN:              new_obj = new Coin(); break;
    case FABRIC_TYPE::POTION_FIRE:       new_obj = new Potion(ELEMENT_TYPE::FIRE); break;
    case FABRIC_TYPE::POTION_POISON:     new_obj = new Potion(ELEMENT_TYPE::POISON); break;
    case FABRIC_TYPE::WEAPON:            new_obj = new Weapon(); break;
    case FABRIC_TYPE::TRAP_SPIKES:       new_obj = new Spikes(); break;
    case FABRIC_TYPE::TRAP_FLAMETHROWER: new_obj = new Flamethrower(); break;
    case FABRIC_TYPE::ENTITY_SKELETON:   new_obj = new Skeleton(); break;
    case FABRIC_TYPE::ENTITY_SPEARMAN:   new_obj = new SkeletonSpearman(); break;
    case FABRIC_TYPE::ENTITY_POTION:     new_obj = new SkeletonPotion(); break;
  }

  if (new_obj != nullptr) {
    LOG("[Obj_Fabric] instantiation of object type ID: " << int(type) << " | ptr: " << new_obj);
  } else {
    ERROR("[Obj_Fabric] Failed to instantiate object for type ID: " << int(type));
  }

  return new_obj;
}

Obj* Obj_Fabric::create_random_reward() {
  std::random_device fabric_rd;
  std::default_random_engine fabric_gen(fabric_rd());
   
  std::uniform_int_distribution<int> dist(1, 4);
  int roll = dist(fabric_gen);

  FABRIC_TYPE selected_type;
  switch (roll) {
      case 1:  selected_type = FABRIC_TYPE::COIN; break;
      case 2:  selected_type = FABRIC_TYPE::POTION_FIRE; break;
      case 3:  selected_type = FABRIC_TYPE::POTION_POISON; break;
      case 4:  selected_type = FABRIC_TYPE::WEAPON; break;
      default: selected_type = FABRIC_TYPE::COIN; break;
  }

  return create_object(selected_type);
}

Obj* Obj_Fabric::create_random_entity() {
  std::random_device fabric_rd;
  std::default_random_engine fabric_gen(fabric_rd());
   
  std::uniform_int_distribution<int> dist(1, 3);
  int roll = dist(fabric_gen);

  FABRIC_TYPE selected_type;
  switch (roll) {
    case 1:  selected_type = FABRIC_TYPE::ENTITY_SKELETON; break;
    case 2:  selected_type = FABRIC_TYPE::ENTITY_SPEARMAN; break;
    case 3:  selected_type = FABRIC_TYPE::ENTITY_POTION; break;
    default: selected_type = FABRIC_TYPE::ENTITY_SKELETON; break;
  }

  return create_object(selected_type);
}

Obj* Obj_Fabric::create_random_trap(std::default_random_engine& gen) {
    std::uniform_int_distribution<int> trap_roll(0, 1);
    FABRIC_TYPE type = (trap_roll(gen) == 0) ? FABRIC_TYPE::TRAP_SPIKES : FABRIC_TYPE::TRAP_FLAMETHROWER;
    return create_object(type);
}

