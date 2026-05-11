#ifndef PLAYER_H
#define PLAYER_H


#include <vector>
#include "constans.h"
#include "element.h"

class player {
 private:
  int level = 1;
  int current_experience = 0;

  int max_hp = PLAYER_BASE_HP;
  int current_hp = PLAYER_BASE_HP;  
  std::pair<ELEMENT_TYPE, int> current_weapon;
  int score = 0;
  
  int position_X;
  int position_Y;

  std::vector< StatusEffect > eff;

 public:
    // Геттеры
  int get_level() const;
  int get_current_experience() const;
  int get_max_hp() const;
  int get_current_hp() const;
  std::pair<ELEMENT_TYPE, int> get_current_weapon() const;
  int get_score() const;
  int get_position_X() const;
  int get_position_Y() const;
  
    // Сеттеры
  void set_level(int lvl);
  void set_current_experience(int exp);
  void set_max_hp(int hp);
  void set_current_hp(int hp);
  void set_current_weapon(std::pair<ELEMENT_TYPE, int> weapon);
  void set_score(int scr);
  void set_position_X(int x);
  void set_position_Y(int y);
  
  void hill(int count = 0 );
  void add_exp(int exp);
  void level_up();
  
  bool is_alive();

  void tik();
  player();

};

#endif //PLAYER_H