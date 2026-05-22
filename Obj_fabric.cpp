#include "Obj_fabric.h"
#include "Log_config.h"

Obj_Fabric& Obj_Fabric::get_instance() {
    static Obj_Fabric instance;
    return instance;
}

Obj* Obj_Fabric::create_object(FABRIC_TYPE type) {
    Obj* new_obj = nullptr;

    switch (type) {
        case FABRIC_TYPE::CHEST:
            new_obj = new Chest();
            break;
        case FABRIC_TYPE::COIN:
            new_obj = new Coin();
            break;
        case FABRIC_TYPE::POTION_FIRE:
            new_obj = new Potion(ELEMENT_TYPE::FIRE);
            break;
        case FABRIC_TYPE::POTION_POISON:
            new_obj = new Potion(ELEMENT_TYPE::POISON);
            break;
        case FABRIC_TYPE::WEAPON:
            new_obj = new Weapon();
            break;
        case FABRIC_TYPE::TRAP_SPIKES:
            new_obj = new Spikes();
            break;
        case FABRIC_TYPE::TRAP_FLAMETHROWER:
            new_obj = new Flamethrower();
            break;
        case FABRIC_TYPE::ENEMY_SKELETON:
            new_obj = new Skeleton();
            break;
        case FABRIC_TYPE::ENEMY_SPEARMAN:
            new_obj = new SkeletonSpearman();
            break;
        case FABRIC_TYPE::ENEMY_POTION:
            new_obj = new SkeletonPotion();
            break;
    }

    if (new_obj != nullptr) {
        LOG("[Obj_Fabric] instantiation of object type : " << int(type) << " : " << new_obj);
    } else {
        ERROR("[Obj_Fabric] Failed to instantiate object for type : " << int(type));
    }

    return new_obj;
}
