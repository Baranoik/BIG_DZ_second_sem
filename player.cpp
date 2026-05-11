#include "player.h"

int player::get_level() const { return level; }
int player::get_current_experience() const { return current_experience; }
int player::get_max_hp() const { return max_hp; }
int player::get_current_hp() const { return current_hp; }
std::pair<ELEMENT_TYPE, int> player::get_current_weapon() const { return current_weapon; }
int player::get_score() const { return score; }
int player::get_position_X() const { return position_X; }
int player::get_position_Y() const { return position_Y; }

// Сеттеры
void player::set_level(int lvl) { level = lvl; }
void player::set_current_experience(int exp) { current_experience = exp; }
void player::set_max_hp(int hp) { max_hp = hp; }
void player::set_current_hp(int hp) { current_hp = hp; }
void player::set_current_weapon(std::pair<ELEMENT_TYPE, int> weapon) { current_weapon = weapon; }
void player::set_score(int scr) { score = scr; }
void player::set_position_X(int x) { position_X = x; }
void player::set_position_Y(int y) { position_Y = y; }


// Остальные методы

bool player::is_alive() {return (0 <= current_hp);}

void player::hill(int count) {
  if (count == 0) {
    current_hp = max_hp;
  } 
  else{
    current_hp = std::min(current_hp + count, max_hp);
  }
}

void player::level_up() {
    max_hp += level;
    hill(); 
}

void player::add_exp( int exp) {
  if (current_experience + exp >= level * PLAYER_LEVEL_UP_DIFICULTY_MULTYPLAER){
    level_up();
    current_experience = std::max(0,level * PLAYER_LEVEL_UP_DIFICULTY_MULTYPLAER - (current_experience + exp) );
  }
  else{
    current_experience += exp;
  }
}

void tik(){
  for (int i = 0; i < eff.size() ; i++)
  {
    /* code */
  }
  
};

player::player() {
  current_weapon = std::make_pair(ELEMENT_TYPE::NONE, PLAYER_BASE_WEAPON_PERFORMANS);
}
