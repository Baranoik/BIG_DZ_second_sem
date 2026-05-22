#ifndef OBJ_FABRIC_H
#define OBJ_FABRIC_H

#include "Obj.h"
#include "Chest.h"
#include "Reward.h"
#include "Trap.h"
#include "Enemy.h"

enum class FABRIC_TYPE {
    CHEST,
    COIN,
    POTION_FIRE,
    POTION_POISON,
    WEAPON,
    TRAP_SPIKES,
    TRAP_FLAMETHROWER,
    ENEMY_SKELETON,
    ENEMY_SPEARMAN,
    ENEMY_POTION
};

class Obj_Fabric {
private:
    Obj_Fabric() = default;
    Obj_Fabric(const Obj_Fabric&) = delete;
    Obj_Fabric& operator=(const Obj_Fabric&) = delete;

public:
    static Obj_Fabric& get_instance();

    // Чистое создание объекта по типу без привязки к координатам
    Obj* create_object(FABRIC_TYPE type);
};

#define FABRIC Obj_Fabric::get_instance()

#endif // OBJ_FABRIC_H
