#ifndef OBJ_FABRIC_H
#define OBJ_FABRIC_H

#include "Obj.h"
#include "Chest.h"
#include "Reward.h"
#include "Trap.h"
#include "Entity.h"
#include <random>

enum class FABRIC_TYPE {
    CHEST,
    COIN,
    POTION_FIRE,
    POTION_POISON,
    WEAPON,
    TRAP_SPIKES,
    TRAP_FLAMETHROWER,
    ENTITY_SKELETON,
    ENTITY_SPEARMAN,
    ENTITY_POTION
};

class Obj_Fabric {
private:
    Obj_Fabric() = default;
    Obj_Fabric(const Obj_Fabric&) = delete;
    Obj_Fabric& operator=(const Obj_Fabric&) = delete;

public:
    static Obj_Fabric& get_instance();

    Obj* create_object(FABRIC_TYPE type);

    Obj* create_random_reward();

    Obj* create_random_entity();

    Obj* create_random_trap(std::default_random_engine& gen);
};

#define FABRIC Obj_Fabric::get_instance()

#endif // OBJ_FABRIC_H
