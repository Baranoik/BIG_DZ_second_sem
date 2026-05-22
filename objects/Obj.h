#ifndef OBJ_H
#define OBJ_H


#include <vector>
#include "constans.h"
#include "element.h"

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
  int soundnes;
  std::vector<StatusEffect> eff_bar;

  
  public:
  Obj();
  virtual ~Obj();
  virtual OBJ_TYPE get_type() const;
  
  virtual bool isdead();
  void apply_eff(const StatusEffect& eff); 
  virtual void tick_eff();
  std::vector<std::string> get_eff_bar() const; 
};




#endif //OBJ_H