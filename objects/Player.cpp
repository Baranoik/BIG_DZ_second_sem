#include "Player.h"
#include "Log_config.h"
#include "constans.h"

Player::Player() : Obj(), score(0), level(1){
  max_hp = PLAYER_BASE_HP;
  soundnes = PLAYER_BASE_HP; 

  weapon_performance[W_DAMAGE]   = PLAYER_BASE_WEAPON_PERFORMANS;
  weapon_performance[W_POISONED] = 0;
  weapon_performance[W_FROZEN]   = 0;
  weapon_performance[W_BURNING]  = 0;
  LOG("Player() : lv " << level << " | hp " << soundnes << " | damage " << PLAYER_BASE_WEAPON_PERFORMANS);
}

bool Player::lv_up_qm() {    
  int required_score = [&]() {
    int base = LEVEL_UP_DIFICULTY * (level + 1);
    return base * base;
  }();
  LOG("lv_up_qw() : " << (score >= required_score));
  return score >= required_score;
}

void Player::lv_up() {
  while (lv_up_qm()) {
    level++;
    max_hp++;
    soundnes = max_hp;
    LOG("lv_up() : lv " << level << " | hp " << max_hp);
  }
}

void Player::add_score(int points) { 
  score += points;
  LOG("add_score() : +" << points);
}

int Player::get_hp() const { return soundnes; }
int Player::get_max_hp() const { return max_hp; }
int Player::get_level() const { return level; }
int Player::get_score() const { return score; }

OBJ_TYPE Player::get_type() const {
  return OBJ_TYPE::PLAYER;
}

bool Player::has_weapon() const {
  return weapon_performance[W_DAMAGE] > 0;
}

int Player::get_weapon_damage() const {
  return weapon_performance[W_DAMAGE];
}

void Player::damage_weapon(int amount) {
  weapon_performance[W_DAMAGE] -= amount;
  if (weapon_performance[W_DAMAGE] < 0) {
    weapon_performance[W_DAMAGE] = 0;
  }
  if (weapon_performance[W_DAMAGE] == 0) {
    LOG("[Player] Weapon broke! Performance reached 0.");
  }
}


void Player::equip_weapon(int base_damage, ELEMENT_TYPE element, int element_duration) {
  weapon_performance[W_DAMAGE] = base_damage;

  weapon_performance[W_POISONED] = 0;
  weapon_performance[W_FROZEN]   = 0;
  weapon_performance[W_BURNING]  = 0;

  switch (element) {
    case ELEMENT_TYPE::POISON:      weapon_performance[W_POISONED] = element_duration; break;
    case ELEMENT_TYPE::ICE:         weapon_performance[W_FROZEN]   = element_duration; break;
    case ELEMENT_TYPE::FIRE:        weapon_performance[W_BURNING]  = element_duration; break;
    default: break; 
  }

  LOG("[Player] Equipped new weapon! Damage: " << base_damage << " | Element: " << int(element));
}
