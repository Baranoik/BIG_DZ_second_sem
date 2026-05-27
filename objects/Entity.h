#ifndef ENTITY_H
#define ENTITY_H

#include "Obj.h"
#include "element.h"

struct LootInfo {
    bool has_loot;
    OBJ_TYPE loot_type;
};

enum class ENEMY_TYPE {
    SKELETON,
    SKELETON_SPEARMAN,
    SKELETON_POTION
};

//=================================================
//                                       Base Enemy
class Enemy : public Obj {
protected:
    LootInfo drop_loot; // Данные о луте, который останется после смерти
public:

    int score_bonus;
    Enemy();
    ~Enemy() override = default;

    OBJ_TYPE get_type() const override;
    
    virtual ENEMY_TYPE get_enemy_type() const = 0;
    LootInfo get_loot_info() const;
    
    virtual StatusEffect get_attack_effect() const;
};

//=================================================
//                                   Skeleton Mobb
class Skeleton : public Enemy {
public:
    Skeleton();
    ~Skeleton() override = default;

    ENEMY_TYPE get_enemy_type() const override;
};

//=================================================
//                            Skeleton Spearman Mobb
class SkeletonSpearman : public Enemy {
public:
    SkeletonSpearman();
    ~SkeletonSpearman() override = default;

    ENEMY_TYPE get_enemy_type() const override;
};

//=================================================
//                              Skeleton Potion Mobb
class SkeletonPotion : public Enemy {
private:
    ELEMENT_TYPE potion_element; // Каким эффектом заражено оружие этого скелета

public:
    SkeletonPotion();
    ~SkeletonPotion() override = default;

    ENEMY_TYPE get_enemy_type() const override;
    
    StatusEffect get_attack_effect() const override;
};

#endif // ENTITY_H
