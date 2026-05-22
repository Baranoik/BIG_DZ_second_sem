#ifndef OBJ_MANAGER_H
#define OBJ_MANAGER_H

#include "Field.h"

class Obj_manager {
private:
    Obj_manager() = default;
    Obj_manager(const Obj_manager&) = delete;
    Obj_manager& operator=(const Obj_manager&) = delete;

public:
    static Obj_manager& get_instance();

    void tick_all_eff();

    void cleanup_dead_objects();

    void rm_at(int x, int y);
    
    void clear_field();
};

#define OBJ_MGR Obj_manager::get_instance()

#endif // OBJ_MANAGER_H