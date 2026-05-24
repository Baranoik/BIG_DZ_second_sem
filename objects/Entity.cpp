#include "Entity.h"
#include "Log_config.h"
#include <random>

// Вспомогательная функция для красивого вывода типа лута в лог
static std::string get_loot_type_name(OBJ_TYPE type) {
  switch (type) {
    case OBJ_TYPE::CHEST:  return "CHEST";
    case OBJ_TYPE::REVARD: return "REWARD";
    default:               return "UNKNOWN";
  }
}

//-------------------------------------------------
//                                       Base Enemy
//-------------------------------------------------
Enemy::Enemy() : Obj(), drop_loot{false, OBJ_TYPE::OBJ} {
  LOG("Enemy() : Base enemy object constructed | " << this);
}

OBJ_TYPE Enemy::get_type() const {
  return OBJ_TYPE::ENTITY; 
}

LootInfo Enemy::get_loot_info() const {
  return drop_loot;
}

StatusEffect Enemy::get_attack_effect() const {
  return StatusEffect(ELEMENT_TYPE::NONE, 0, 0);
}

//-------------------------------------------------
//                                   Skeleton Mobb
//-------------------------------------------------
Skeleton::Skeleton() : Enemy() {
  std::random_device enemy_rd;
  std::default_random_engine enemy_gen(enemy_rd());
  
  std::uniform_int_distribution<int> hp_dist(8, 12);
  soundnes = hp_dist(enemy_gen);

  std::uniform_int_distribution<int> chance_dist(1, 100);
  if (chance_dist(enemy_gen) <= 40) {
    drop_loot = {true, OBJ_TYPE::REVARD};
  }

  // ИСПРАВЛЕНО: Логируем лут красиво и только если он реально есть
  if (drop_loot.has_loot) {
    LOG("Skeleton() : Spawned | soundnes (HP): " << soundnes 
      << " | loot: [" << get_loot_type_name(drop_loot.loot_type) << "] | " << this);
  } else {
    LOG("Skeleton() : Spawned | soundnes (HP): " << soundnes << " | loot: [NO] | " << this);
  }
}

ENEMY_TYPE Skeleton::get_enemy_type() const {
  return ENEMY_TYPE::SKELETON;
}

//-------------------------------------------------
//                            Skeleton Spearman Mobb
//-------------------------------------------------
SkeletonSpearman::SkeletonSpearman() : Enemy() {
  std::random_device enemy_rd;
  std::default_random_engine enemy_gen(enemy_rd());
  
  std::uniform_int_distribution<int> hp_dist(12, 16);
  soundnes = hp_dist(enemy_gen);

  std::uniform_int_distribution<int> chance_dist(1, 100);
  if (chance_dist(enemy_gen) <= 50) {
    drop_loot = {true, OBJ_TYPE::CHEST};
  }

  // ИСПРАВЛЕНО: Логируем лут красиво и только если он реально есть
  if (drop_loot.has_loot) {
    LOG("SkeletonSpearman() : Spawned | soundnes (HP): " << soundnes 
      << " | loot: [" << get_loot_type_name(drop_loot.loot_type) << "] | " << this);
  } else {
    LOG("SkeletonSpearman() : Spawned | soundnes (HP): " << soundnes << " | loot: [NO] | " << this);
  }
}

ENEMY_TYPE SkeletonSpearman::get_enemy_type() const {
  return ENEMY_TYPE::SKELETON_SPEARMAN;
}

//-------------------------------------------------
//                              Skeleton Potion Mobb
//-------------------------------------------------
SkeletonPotion::SkeletonPotion() : Enemy() {
  std::random_device enemy_rd;
  std::default_random_engine enemy_gen(enemy_rd());
  
  std::uniform_int_distribution<int> hp_dist(6, 9);
  soundnes = hp_dist(enemy_gen);

  std::uniform_int_distribution<int> element_dist(1, 2);
  int roll = element_dist(enemy_gen);
  
  switch (roll) {
    case 1:  potion_element = ELEMENT_TYPE::FIRE; break;
    default: potion_element = ELEMENT_TYPE::POISON; break;
  }

  std::uniform_int_distribution<int> chance_dist(1, 100);
  if (chance_dist(enemy_gen) <= 60) {
    drop_loot = {true, OBJ_TYPE::REVARD};
  }

  // ИСПРАВЛЕНО: Логируем лут красиво и только если он реально есть
  if (drop_loot.has_loot) {
    LOG("SkeletonPotion() : Spawned | soundnes (HP): " << soundnes 
      << " | element: " << int(potion_element) 
      << " | loot: [" << get_loot_type_name(drop_loot.loot_type) << "] | " << this);
  } else {
    LOG("SkeletonPotion() : Spawned | soundnes (HP): " << soundnes 
      << " | element: " << int(potion_element) << " | loot: [NO] | " << this);
  }
}

ENEMY_TYPE SkeletonPotion::get_enemy_type() const {
  return ENEMY_TYPE::SKELETON_POTION;
}

StatusEffect SkeletonPotion::get_attack_effect() const {
  return StatusEffect(potion_element, 2);
}
