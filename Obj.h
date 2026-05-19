#ifndef OBJ_H
#define OBJ_H


#include <vector>
#include "constans.h"

enum class OBJ_TYPE{
  OBJ,
  ENTITY,
  TRAP,
  CHEST,
  REVARD,
  PLAYER
};

class Obj{

 protected:
  int curent_performas;
  bool virtual isdead();

 public:
  Obj();
  virtual ~Obj();
  virtual OBJ_TYPE get_type() const; 
};




#endif //OBJ_H