#ifndef PLAYER_H
#define PLAYER_H

#include "Obj.h"
#include "constans.h"
class Reward; 

class Player : public Obj {
 private:
 
  int level;
  int score;
  
  int max_hp;
  int& current_hp; 

  int weapon_performance[W_SIZE]; 
 
  public:

  Player();
  ~Player() override = default;


// Уникальные методы игрока
  bool lv_up_qm();
  void lv_up(int lv = 1);

// Геттеры и сеттеры
  int get_hp() const;
  int get_max_hp() const;
  int get_level() const;
  int get_score() const;
  void add_score(int points);

  OBJ_TYPE get_type() const override; 
};

#endif // PLAYER_H
