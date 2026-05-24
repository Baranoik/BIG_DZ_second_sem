#include "Player.h"
#include "Log_config.h"
#include "constans.h"

Player::Player() 
    : Obj(), 
      score(0),
      level(1)
{
    max_hp = PLAYER_BASE_HP;
    soundnes = PLAYER_BASE_HP; // Напрямую задаем базовое здоровье в soundness

    // Инициализируем стартовое оружие игрока [урон, яд, холод, огонь]
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

void Player::lv_up(int lv) {
  while (lv_up_qm()) {
    level++;
    max_hp++;
    soundnes = max_hp; // Восстанавливаем здоровье до нового максимума
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
