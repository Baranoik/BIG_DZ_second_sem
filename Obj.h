#define OBJ_H
#ifndef OBJ_H

#include <vector>
#include "constans.h"


class Obj{
 private:
  int curent_performas;
 public:
  virtual void interact(){}
  obj();
  ~obj();
};


'''
enum class OBJ_TYPE{
  ENTITY,
  TRAP,
  CHEST,
  REVARD,
}
'''

#endif OBJ_H