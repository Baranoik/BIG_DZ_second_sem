#include "Obj_manager.h"
#include "Obj_fabric.h" // Подключаем фабрику для вызова спавна объектов
#include "Log_config.h"
#include <random>
#include <vector>

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
     LOG("[Obj_manager] remove_at: Tried to delete Player at {" << x << "} - Ignored.");
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

int Obj_manager::count_objects_by_type(OBJ_TYPE type) const {
  int count = 0;
  for (int x = 0; x < GRID_SIZE_X; ++x) {
    for (int y = 0; y < GRID_SIZE_Y; ++y) {
      Obj* obj = FIELD.get_Obj(x, y);
      if (obj != nullptr && obj->get_type() == type) {
        count++;
      }
    }
  }
  return count;
}

int Obj_manager::count_empty_cells() const {
  int count = 0;
  for (int x = 0; x < GRID_SIZE_X; ++x) {
    for (int y = 0; y < GRID_SIZE_Y; ++y) {
      if (FIELD.get_Obj(x, y) == nullptr) {
        count++;
      }
    }
  }
  return count;
}

void Obj_manager::check_and_refill_field() {
  int empty_count = count_empty_cells();
  if (empty_count <= 3) {
    return; 
  }

  LOG("[Obj_manager] Empty cells count: " << empty_count << " (> 3). Starting random refill phase!");

  std::random_device rd;
  std::default_random_engine gen(rd());
    
  std::discrete_distribution<int> spawn_dist({60, 40});
  std::discrete_distribution<int> type_dist({45, 35, 20});

  std::vector<std::pair<int, int>> empty_cells;

  for (int x = 0; x < GRID_SIZE_X; ++x) {
    for (int y = 0; y < GRID_SIZE_Y; ++y) {
      if (FIELD.get_Obj(x, y) == nullptr) {
        empty_cells.push_back(std::make_pair(x, y));
      }
    }
  }

  for (const auto& cell : empty_cells) {
      
    if (spawn_dist(gen) == 0) {
      continue; 
    }

    int type_roll = type_dist(gen);
    Obj* new_obj = nullptr;

    if (type_roll == 0) {
      new_obj = FABRIC.create_random_reward();
    } 
    else if (type_roll == 1) {
      new_obj = FABRIC.create_random_entity();
    } 
    else {
      new_obj = FABRIC.create_random_trap(gen); 
    }

    if (new_obj != nullptr) {
      FIELD.set_Obj(cell.first, cell.second, new_obj);
      LOG("[Obj_manager] Spawned random obj on empty cell {" << cell.first << ";" << cell.second << "}");
    }
  }
}
