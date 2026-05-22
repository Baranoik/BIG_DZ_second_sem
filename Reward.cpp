#include "Reward.h"
#include "Log_config.h"
#include <random>
/*


        МАГИЧЕСКИЕ ЧИСЛА БРО

*/


//-------------------------------------------------
//                                    Base Reward
//-------------------------------------------------
Reward::Reward() : Obj() {
  LOG("Reward() : Base reward object constructed | " << this);
}

OBJ_TYPE Reward::get_type() const {
  return OBJ_TYPE::REVARD; 
}

//-------------------------------------------------
//                                   Coin Reward
//-------------------------------------------------
Coin::Coin() : Reward() {
  std::random_device reward_rd;
  std::default_random_engine reward_gen(reward_rd());
  std::uniform_int_distribution<int> gold_dist(10, 50);

  soundnes = gold_dist(reward_gen);
  LOG("Coin() : Created coin reward | soundnes (gold): " << soundnes << " | " << this);
}

REWARD_TYPE Coin::get_reward_type() const {
  return REWARD_TYPE::COIN;
}

int Coin::get_gold_amount() const {
  return soundnes;
}

//-------------------------------------------------
//                                 Potion Reward
//-------------------------------------------------
Potion::Potion(ELEMENT_TYPE effect_type) 
  : Reward(), 
    effect(effect_type, 1)
{
  soundnes = 1;

  std::random_device reward_rd;
  std::default_random_engine reward_gen(reward_rd());
  std::uniform_int_distribution<int> duration_dist(2, 5);

  int random_duration = duration_dist(reward_gen);
   
  effect = StatusEffect(effect_type, random_duration);

  LOG("Potion() : Created potion using auto-effect | type: " << int(effect.type) 
    << " | dur: " << effect.duration << " | dps: " << effect.damage << " | " << this);
}

REWARD_TYPE Potion::get_reward_type() const {
  return REWARD_TYPE::POTION;
}

StatusEffect Potion::get_effect() const {
  return effect;
}

//-------------------------------------------------
//                                 Weapon Reward
//-------------------------------------------------
Weapon::Weapon() 
  : Reward(),
    elemental_type(ELEMENT_TYPE::NONE),
    weapon_effect(ELEMENT_TYPE::NONE, 0)
{
  std::random_device reward_rd;
  std::default_random_engine reward_gen(reward_rd());
   
  std::uniform_int_distribution<int> dmg_dist(5, 15);
  soundnes = dmg_dist(reward_gen);

  std::uniform_int_distribution<int> chance_dist(1, 100);
    
  if (chance_dist(reward_gen) <= 30) {
    std::uniform_int_distribution<int> element_dist(1, 3);
    int roll = element_dist(reward_gen);
        
    switch (roll) {
      case 1: elemental_type = ELEMENT_TYPE::FIRE; break;
      case 2: elemental_type = ELEMENT_TYPE::ICE; break;
      case 3: elemental_type = ELEMENT_TYPE::POISON; break;
     default: elemental_type = ELEMENT_TYPE::NONE; break;
    }
        
    // Рандомизируем длительность эффекта на оружии (например, от 2 до 4 ходов)
    std::uniform_int_distribution<int> eff_dur_dist(2, 4);
    int random_duration = eff_dur_dist(reward_gen);
       
    // Автоматически создаем эффект по правилам StatusEffect
    weapon_effect = StatusEffect(elemental_type, random_duration);
    }

  LOG("Weapon() : Created weapon | soundnes (damage): " << soundnes 
    << " | element type: " << int(elemental_type) 
    << " | eff dur: " << weapon_effect.duration << " | " << this);
}

REWARD_TYPE Weapon::get_reward_type() const {
  return REWARD_TYPE::WEAPON;
}

int Weapon::get_damage_performance() const {
  return soundnes; 
}

ELEMENT_TYPE Weapon::get_elemental_type() const {
  return elemental_type;
}

StatusEffect Weapon::get_weapon_effect() const {
  return weapon_effect;
}