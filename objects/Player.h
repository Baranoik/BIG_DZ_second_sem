#ifndef PLAYER_H
#define PLAYER_H

#include "Obj.h"
#include "constans.h"

class Player : public Obj {
 private:
  int level;
  int score;
  int max_hp;
  int weapon_performance[W_SIZE]; 
 
 public:
  Player();
  ~Player() override = default;

  bool lv_up_qm();
  void lv_up();

  bool has_weapon() const;
  int get_weapon_damage() const;
  void damage_weapon(int amount);

  void equip_weapon(int base_damage, ELEMENT_TYPE element, int element_duration);

  
  int get_hp() const;
  int get_max_hp() const;
  int get_level() const;
  int get_score() const;
  void add_score(int points);

  OBJ_TYPE get_type() const override; 
};

#endif // PLAYER_H
