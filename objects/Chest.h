#ifndef CHEST_H
#define CHEST_H

#include "Obj.h"

class Chest : public Obj {
public:
  Chest();
  ~Chest() override;

  OBJ_TYPE get_type() const override;
};

#endif // CHEST_H