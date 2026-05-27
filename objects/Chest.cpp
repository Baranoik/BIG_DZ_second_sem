#include "Chest.h"
#include "Log_config.h"

Chest::Chest() : Obj() {
  soundnes = CHEST_BASE_HP;
  LOG("Chest() : Created new chest | soundnes " << soundnes << " | " << this);
}

Chest::~Chest() {
  LOG("~Chest() : Destroying chest object | " << this);
}

OBJ_TYPE Chest::get_type() const {
  return OBJ_TYPE::CHEST;
}