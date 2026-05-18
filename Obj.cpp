#include "Obj.h"
#include "Log_config.h"

Obj::Obj() : type(OBJ_TYPE::ENTITY), curent_performas(0) {
  LOG("Obj() : "<<this);
}
Obj::~Obj() {
  LOG("~Obj : "<<this);
}