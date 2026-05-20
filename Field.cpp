#include "Field.h"
#include "Log_config.h"

Field::Field() {
  for (int x = 0; x < GRID_SIZE_X; ++x) {
    for (int y = 0; y < GRID_SIZE_Y; ++y) {
      XYnet[x][y] = nullptr;
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
  if (XYnet[x][y] != nullptr) {
    LOG("set_Obj : {"<<x<<";"<<y<< "} alredy occupaed");
    return;
  }
  XYnet[x][y] = obj;
  LOG("set_Obj : "<<obj<<" on {"<<x<<";"<<y<<"}");
}

Obj* Field::get_Obj(int x, int y) const {
  if (!isin(x, y)) {
    LOG("get_Obj : no Obj");
    return nullptr;
  }
  LOG("get_Obj : "<<XYnet[x][y]);
  return XYnet[x][y];
}

void Field::rm_Obj(int x, int y) {
  if (!isin(x, y)) {
    LOG("remove_Obj() : position out of bounds");
    return;
  }

  Obj* target = XYnet[x][y];
  if (target == nullptr) {
    LOG("remove_Obj : nothing to remove on {" << x << ";" << y << "}");
    return;
  }

  XYnet[y][x] = nullptr;
  LOG("remove_Obj : deleting object on {" << x << ";" << y << "}");
  delete target; 
}
void Field::print_field() const {
  std::cout << "\n"; // Отступ перед полем
  for (int x = 0; x < GRID_SIZE_X; ++x) {
    for (int y = 0; y < GRID_SIZE_Y; ++y) {
      if (XYnet[x][y] == nullptr) {
        std::cout << "[emp]\t"; // Если клетка пустая
      } else {
        std::cout << "[ "<<int(XYnet[x][y]->get_type())<<" ]\t"; // Если в клетке есть объект
      }
    }
    std::cout << "\n"; // Перенос строки в конце каждого ряда
  }
  std::cout << "\n";
}