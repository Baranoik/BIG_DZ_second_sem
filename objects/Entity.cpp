#include "Entity.h"
#include "Log_config.h"
#include <random>

//-------------------------------------------------
//                                       Base Enemy
//-------------------------------------------------
Enemy::Enemy() : Obj(), drop_loot{false, OBJ_TYPE::OBJ} {
    LOG("Enemy() : Base enemy object constructed | " << this);
}

OBJ_TYPE Enemy::get_type() const {
    return OBJ_TYPE::ENTITY; // Воспользуемся типом ENTITY из твоего enum для мобов
}

LootInfo Enemy::get_loot_info() const {
    return drop_loot;
}

int Enemy::get_attack_power() const {
    // Базовая логика: урон зависит от текущего soundnes моба (чем он слабее, тем меньше бьет)
    return soundnes ;
}

//-------------------------------------------------
//                                   Skeleton Mobb
//-------------------------------------------------
Skeleton::Skeleton() : Enemy() {
    std::random_device enemy_rd;
    std::default_random_engine enemy_gen(enemy_rd());
    
    // Обычный скелет: среднее ХП (soundnes)
    std::uniform_int_distribution<int> hp_dist(8, 12);
    soundnes = hp_dist(enemy_gen);

    // Настройка лута: 40% шанс, что выпадет обычная награда (REWARD)
    std::uniform_int_distribution<int> chance_dist(1, 100);
    if (chance_dist(enemy_gen) <= 40) {
        drop_loot = {true, OBJ_TYPE::REVARD};
    }

    LOG("Skeleton() : Spawned | soundnes (HP): " << soundnes 
        << " | loot: " << (drop_loot.has_loot ? "[YES]" : "[NO]") << " | " << this);
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
    
    // Скелет-копейщик: более живучий
    std::uniform_int_distribution<int> hp_dist(12, 16);
    soundnes = hp_dist(enemy_gen);

    // Настройка лута: у копейщика 50% шанс оставить после себя целый сундук (CHEST)
    std::uniform_int_distribution<int> chance_dist(1, 100);
    if (chance_dist(enemy_gen) <= 50) {
        drop_loot = {true, OBJ_TYPE::CHEST};
    }

    LOG("SkeletonSpearman() : Spawned | soundnes (HP): " << soundnes 
        << " | loot: " << (drop_loot.has_loot ? "[CHEST]" : "[NO]") << " | " << this);
}

ENEMY_TYPE SkeletonSpearman::get_enemy_type() const {
    return ENEMY_TYPE::SKELETON_SPEARMAN;
}

int SkeletonSpearman::get_attack_power() const {
    // Копейщик бьет сильнее обычного скелета
    return soundnes;
}

//-------------------------------------------------
//                              Skeleton Potion Mobb
//-------------------------------------------------
SkeletonPotion::SkeletonPotion() : Enemy() {
  std::random_device enemy_rd;
  std::default_random_engine enemy_gen(enemy_rd());
    
  // Скелет с зельем: хлипкий, но опасный из-за эффектов
  std::uniform_int_distribution<int> hp_dist(6, 9);
  soundnes = hp_dist(enemy_gen);

  // Выбираем случайный эффект для его атак (1 - огонь, 3 - яд)
  std::uniform_int_distribution<int> element_dist(1, 2);
  int roll = element_dist(enemy_gen);
    
  switch (roll) {
    case 1:  potion_element = ELEMENT_TYPE::FIRE; break;
    default: potion_element = ELEMENT_TYPE::POISON; break;
  }

 // Настройка лута: 60% шанс выронить награду (обычно зелье)
 std::uniform_int_distribution<int> chance_dist(1, 100);
  if (chance_dist(enemy_gen) <= 60) {
    drop_loot = {true, OBJ_TYPE::REVARD};
  }

  LOG("SkeletonPotion() : Spawned | soundnes (HP): " << soundnes 
    << " | element: " << int(potion_element) 
    << " | loot: " << (drop_loot.has_loot ? "[YES]" : "[NO]") << " | " << this);
}

ENEMY_TYPE SkeletonPotion::get_enemy_type() const {
  return ENEMY_TYPE::SKELETON_POTION;
}

StatusEffect SkeletonPotion::get_attack_effect() const {
  return StatusEffect(potion_element, 2);
}
