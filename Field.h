#include <iostream>
#include "constans.h"
#include "Obj.h"

//=================================================
//                                          XYnet 

struct XYnet{
  
  Obj matrix[GRID_SIZE_Y][GRID_SIZE_X] = { nullptr } 
}



//=================================================
//                                           Field


class Field {
 private:

  Field() {}
    
  Field(const Field&) = delete;
  Field& operator=(const Field&) = delete;

 public:
  static Field& get_instance() {
    static Field instance;
    return instance;
  }

};

#define FIELD Field::get_instance()