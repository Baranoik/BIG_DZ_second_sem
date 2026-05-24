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
    ERROR("set_Obj() : {"<< x <<";"<< y <<"} is not in {"<<GRID_SIZE_X<<";"<<GRID_SIZE_Y<<"}"); 
    return;
  }
  if (XYnet[x][y] != nullptr) {
    LOG("set_Obj() : {"<<x<<";"<<y<< "} alredy occupaed");
    return;
  }
  XYnet[x][y] = obj;
  LOG("set_Obj() : "<<obj<<" on {"<<x<<";"<<y<<"}");
}

Obj* Field::get_Obj(int x, int y) const {
  if (!isin(x, y)) {
    LOG("get_Obj() : no Obj");
    return nullptr;
  }
  LOG("get_Obj() : "<<XYnet[x][y]);
  return XYnet[x][y];
}

void Field::rm_Obj(int x, int y) {
  if (!isin(x, y)) {
    LOG("remove_Obj() : position out of bounds");
    return;
  }

  Obj* target = XYnet[x][y];
  if (target == nullptr) {
    LOG("remove_Obj() : nothing to remove on {" << x << ";" << y << "}");
    return;
  }

  XYnet[x][y] = nullptr;
  LOG("remove_Obj() : deleting object on {" << x << ";" << y << "}");
  delete target; 
}

// В конец файла Field.cpp
void Field::move_Obj(int from_x, int from_y, int to_x, int to_y) {
  if (!isin(from_x, from_y)) {
    ERROR("move_Obj() : Source coordinates {" << from_x << ";" << from_y << "} out of bounds!");
    return;
  }
  if (!isin(to_x, to_y)) {
    ERROR("move_Obj() : Destination coordinates {" << to_x << ";" << to_y << "} out of bounds!");
    return;
  }

  Obj* moving_obj = XYnet[from_x][from_y];
  if (moving_obj == nullptr) {
    LOG("move_Obj() : No object found at source {" << from_x << ";" << from_y << "} to move.");
    return;
  }

  if (XYnet[to_x][to_y] != nullptr) {
    LOG("move_Obj() : Cannot move! Destination {" << to_x << ";" << to_y << "} is already occupied.");
    return;
  }

  XYnet[to_x][to_y] = moving_obj;
  XYnet[from_x][from_y] = nullptr;

  LOG("move_Obj() : Object " << moving_obj << " successfully moved from {" 
    << from_x << ";" << from_y << "} to {" << to_x << ";" << to_y << "}");
}

void Field::print_field() const {
  std::cout << "\n  --- ТЕКУЩЕЕ СОСТОЯНИЕ ПОЛЯ ---";
  std::cout << "\n"; 
  for (int x = 0; x < GRID_SIZE_X; ++x) {
    for (int y = 0; y < GRID_SIZE_Y; ++y) {
      if (XYnet[x][y] == nullptr) {
        std::cout << "[ emp ]  "; 
      } else {
        // Проверяем тип объекта и выводим красивый маркер
        switch (XYnet[x][y]->get_type()) {
          case OBJ_TYPE::PLAYER: std::cout << "[=PLR=]  "; break;
          case OBJ_TYPE::CHEST:  std::cout << "[ CHS ]  "; break;
          case OBJ_TYPE::TRAP:   std::cout << "[ TRP ]  "; break;
          case OBJ_TYPE::REVARD: std::cout << "[ REW ]  "; break;
          case OBJ_TYPE::ENTITY: std::cout << "[ ENM ]  "; break;
          default:               std::cout << "[ ??? ]  "; break;
        }
      }
    }
    std::cout << "\n";
  }
  std::cout << "  -------------------------------\n\n";
}
