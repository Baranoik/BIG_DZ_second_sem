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
  StatusEffect(ELEMENT_TYPE t, int dur, int dps = 0){
    type = t; duration = dur; damage = dps;
    LOG("StatusEffect() : "<< this->get_title()<<" | duration "<< dur<<" | dps "<<dps );
  };
  std::string get_title() const {
    switch (type) {
      case ELEMENT_TYPE::FIRE:        return "[Fire]";
      case ELEMENT_TYPE::ICE:         return "[Ice]";
      case ELEMENT_TYPE::POISON:      return "[Poison]";
      case ELEMENT_TYPE::REGENRATION: return "[Regeneration]";
      default:                        ERROR("get_title() : " << "indefined effect please chek : [element.h] and make shure get_title() got instruction for all  ELEMENT_TYPE");
    }
  }
};


#endif //ELEMENT_H