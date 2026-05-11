#ifndef ELEMENT_H
#define ELEMENT_H

#include "constans.h"

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
  };
};


#endif //ELEMENT_H