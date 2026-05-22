#ifndef ENEMY_H
#define ENEMY_H

#include "Obj.h"
#include "element.h"

// Структура «излута»: выпадает ли что-то, и какого типа объект
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
    Enemy();
    ~Enemy() override = default;

    OBJ_TYPE get_type() const override;
    
    virtual ENEMY_TYPE get_enemy_type() const = 0;
    
    // Геттер для получения информации о луте (для фабрики/менеджера)
    LootInfo get_loot_info() const;
    
    // Геттер урона врага (привяжем к soundnes или сделаем виртуальным)
    virtual int get_attack_power() const;
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
    ELEMENT_TYPE potion_element; // Каким эффектом заражены стрелы/оружие этого скелета

public:
    SkeletonPotion();
    ~SkeletonPotion() override = default;

    ENEMY_TYPE get_enemy_type() const override;
    
    // Возвращает эффект, который этот скелет накладывает при ударе
    StatusEffect get_attack_effect() const;
};

#endif // ENEMY_H