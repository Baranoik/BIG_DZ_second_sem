#ifndef ELEMENT_H
#define ELEMENT_H

#include <iostream>
#include "constans.h"
#include "Log_config.h"

enum class ELEMENT_TYPE {
  NONE   = ELEMENT_NONE,
  FIRE   = ELEMENT_FIRE,
  ICE    = ELEMENT_ICE,
  POISON = ELEMENT_POISON,
  REGENRATION = ELEMENT_REG
};

struct StatusEffect {
  ELEMENT_TYPE type;
  int duration;
  int damage;

  StatusEffect(ELEMENT_TYPE t, int dur, int dps) {
    type = t; duration = dur; damage = dps;
    LOG("StatusEffect(Full) : " << this->get_title() << " | duration " << dur << " | dps " << dps);
  }

  StatusEffect(ELEMENT_TYPE t, int dur) {
    type = t;
    duration = dur;
    
    switch (t) {
      case ELEMENT_TYPE::POISON:
        damage = POISON_DAMAGE;
        break;
      case ELEMENT_TYPE::FIRE:
        damage = BURN_DAMAGE;
        break;
      case ELEMENT_TYPE::REGENRATION:
        damage = -1;
        break;
      default:
        damage = 0; 
        break;
    }
    LOG("StatusEffect(Auto) : " << this->get_title() << " | duration " << dur << " | auto-dps " << damage);
  }

  std::string get_title() const {
    switch (type) {
      case ELEMENT_TYPE::NONE:        return "[None]";
      case ELEMENT_TYPE::FIRE:        return "[Fire]";
      case ELEMENT_TYPE::ICE:         return "[Ice]";
      case ELEMENT_TYPE::POISON:      return "[Poison]";
      case ELEMENT_TYPE::REGENRATION: return "[Regen]";
      default:                        ERROR("get_title() : " << "indefined effect please chek : [element.h] and make shure get_title() got instruction for all  ELEMENT_TYPE");
    }
  }
};


#endif //ELEMENT_H