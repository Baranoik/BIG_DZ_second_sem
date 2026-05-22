#include "Obj_manager.h"
#include "Log_config.h"

Obj_manager& Obj_manager::get_instance() {
  static Obj_manager instance;
  return instance;
}

void Obj_manager::tick_all_eff() {
  LOG("[Obj_manager] ---> Phase: Ticking Effects <---");
  for (int x = 0; x < GRID_SIZE_X; ++x) {
    for (int y = 0; y < GRID_SIZE_Y; ++y) {
      Obj* obj = FIELD.get_Obj(x, y);
      if (obj != nullptr) {
        obj->tick_eff();
      }
    }
  }
}

void Obj_manager::cleanup_dead_objects() {
  LOG("[Obj_manager] ---> Phase: Cleaning Up Dead Objects <---");
  for (int x = 0; x < GRID_SIZE_X; ++x) {
    for (int y = 0; y < GRID_SIZE_Y; ++y) {
    Obj* obj = FIELD.get_Obj(x, y);

    if (obj != nullptr && obj->isdead()) {
             
      LOG("[Obj_manager] Removing dead object from {" << x << ";" << y << "}");
      FIELD.rm_Obj(x, y); 
      }
    }
  }
}

void Obj_manager::rm_at(int x, int y) {
  Obj* obj = FIELD.get_Obj(x, y);
    
  if (obj == nullptr) {
    LOG("[Obj_manager] remove_at: cell {" << x << ";" << y << "} is already empty.");
    return;
  }

  if (obj->get_type() == OBJ_TYPE::PLAYER) {
     LOG("[Obj_manager] remove_at: Tried to delete Player at {" << x << ";" << y << "} - Ignored.");
    return;
  }

  LOG("[Obj_manager] remove_at: deleting object at {" << x << ";" << y << "}");
  FIELD.rm_Obj(x, y);
}

void Obj_manager::clear_field() {
  LOG("[Obj_manager] Wiping field...");
  for (int x = 0; x < GRID_SIZE_X; ++x) {
    for (int y = 0; y < GRID_SIZE_Y; ++y) {
      if (FIELD.get_Obj(x, y) != nullptr) {
        FIELD.rm_Obj(x, y);
      }
    }
  }
}
