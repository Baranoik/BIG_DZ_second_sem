#ifndef OBJ_H
#define OBJ_H


#include <vector>
#include "constans.h"

enum class OBJ_TYPE{
  ENTITY,
  TRAP,
  CHEST,
  REVARD,
};

class Obj{
 private:
  OBJ_TYPE type ;
  int curent_performas;
 public:
  virtual void interact(){}
  Obj();
  ~Obj();
};




#endif //OBJ_H