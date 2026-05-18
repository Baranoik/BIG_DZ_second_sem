#include "Field.h"
#include "Log_config.h"

Field::Field() {
  for (int y = 0; y < GRID_SIZE_Y; ++y) {
    for (int x = 0; x < GRID_SIZE_X; ++x) {
      XYnet[y][x] = nullptr;
    }
  }
}

bool Field::isin(int x, int y) const {
  return (x >= 0 && x < GRID_SIZE_X && y >= 0 && y < GRID_SIZE_Y);
}

Field& Field::get_instance() {
    static Field instance;
    return instance;
}
    
void Field::set_Obj(int x, int y, Obj* obj) {
  if (!isin(x, y)){
    ERROR("set_Obj : {"<< x <<";"<< y <<"} is not in {"<<GRID_SIZE_X<<";"<<GRID_SIZE_Y<<"}"); 
    return;
  }
  if (XYnet[y][x] != nullptr) {
    LOG("set_Obj : {"<<x<<";"<<y<< "} alredy occupaed");
    return;
  }
  XYnet[y][x] = obj;
  LOG("set_Obj : "<<obj<<" on {"<<x<<";"<<y<<"}");
}

Obj* Field::get_Obj(int x, int y) const {
  if (!isin(x, y)) {
    LOG("get_Obj : no Obj");
    return nullptr;
  }
  LOG("get_Obj : "<<XYnet[y][x]);
  return XYnet[y][x];
}

void Field::print_field() const {
  std::cout << "\n"; // Отступ перед полем
  for (int y = 0; y < GRID_SIZE_Y; ++y) {
    for (int x = 0; x < GRID_SIZE_X; ++x) {
      if (XYnet[y][x] == nullptr) {
        std::cout << "[emp]\t"; // Если клетка пустая
      } else {
        std::cout << "[obj]\t"; // Если в клетке есть объект
      }
    }
    std::cout << "\n"; // Перенос строки в конце каждого ряда
  }
  std::cout << "\n";
}