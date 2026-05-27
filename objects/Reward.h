#ifndef REWARD_H
#define REWARD_H

#include "Obj.h"
#include "element.h"

enum class REWARD_TYPE {
  COIN,
  WEAPON,
  POTION
};

//=================================================
//                                    Base Reward
class Reward : public Obj {
public:
  Reward();
  ~Reward() override = default;

  OBJ_TYPE get_type() const override;
  virtual REWARD_TYPE get_reward_type() const = 0;
};

//=================================================
//                                   Coin Reward
class Coin : public Reward {
public:
  Coin();
  ~Coin() override = default;

  REWARD_TYPE get_reward_type() const override;
  int get_gold_amount() const;
};

//=================================================
//                                 Potion Reward
class Potion : public Reward {
private:
  StatusEffect effect;

public:
  Potion(ELEMENT_TYPE effect_type);
  ~Potion() override = default;

  REWARD_TYPE get_reward_type() const override;
  StatusEffect get_effect() const;
};

//=================================================
//                                 Weapon Reward
class Weapon : public Reward {
private:
  ELEMENT_TYPE elemental_type; 
  StatusEffect weapon_effect;  

public:
  Weapon();
  ~Weapon() override = default;

  REWARD_TYPE get_reward_type() const override;
    
  int get_damage_performance() const;
  ELEMENT_TYPE get_elemental_type() const;
  StatusEffect get_weapon_effect() const;
};

#endif // REWARD_H