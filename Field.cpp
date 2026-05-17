#include "Field.h"
#include "Log_config.h"

bool Field::isin(int x, int y) const {
  return (x >= 0 && x < GRID_SIZE_X && y >= 0 && y < GRID_SIZE_Y);
}

 static Field& Field::get_instance() {
    static Field instance;
    return instance;
  };
    
void Field::set_Obj(int x, int y, Obj* obj) {
  if (!isin(x, y)){
    ERROR <<"set_Obj : {"<< x <<";"<< y <<"} is not in {"<<GRID_SIZE_X<<";"<<GRID_SIZE_Y<<"}"; 
    break;
  }
  if (net.matrix[y][x] != nullptr) {
    LOG<<"set_Obj :{"<<x<<";"<<y<< "} alredy occupaed";
    break;
  }
  XYnet.matrix[y][x] = obj;
  LOG<<"set_Obj : new obj on {"<<x<<";"<<y<<"}";
}


Obj* Field::getObj(int x, int y) const {
  if (!isInside(x, y)) {
    LOG<<"get_Obj : no Obj"
    return nullptr;
  }
  LOG<<"get_Obj : success";
  return XYnet.matrix[y][x];
}