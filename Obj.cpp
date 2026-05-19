#include "Obj.h"
#include "Log_config.h"

Obj::Obj() : curent_performas(0) {
  LOG("Obj() : "<<this);
}
Obj::~Obj() {
  LOG("~Obj : "<<this);
}

bool Obj::isdead(){
  return curent_performas<=0;
}

OBJ_TYPE Obj::get_type() const {
  return OBJ_TYPE::OBJ; 
}