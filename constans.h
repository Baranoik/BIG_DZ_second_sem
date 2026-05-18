// Все магические числа и параметры игры вынесены сюда.
// Никаких "голых" чисел в остальных файлах проекта.
#ifndef CONSTANS_H
#define CONSTANS_H

//----------------------------------------------
// Размеры поля
//----------------------------------------------
#define GRID_SIZE_X 3
#define GRID_SIZE_Y 3

//----------------------------------------------
// Игрок
//----------------------------------------------
#define PLAYER_BASE_HP 10
#define PLAYER_BASE_WEAPON_PERFORMANS 11
#define PLAYER_LEVEL_UP_DIFICULTY_MULTYPLAER 3

//----------------------------------------------
// Идентификаторы стихий (для инициализации перечислений)
//----------------------------------------------
#define ELEMENT_NONE    0
#define ELEMENT_FIRE    1
#define ELEMENT_ICE     2
#define ELEMENT_POISON  3
#define ELEMENT_REG     4

//----------------------------------------------
// Длительности и урон статусных эффектов
//----------------------------------------------
#define BURN_DURATION   3
#define BURN_DAMAGE     1
#define FROZEN_DURATION 2
#define POISON_DURATION 3
#define POISON_DAMAGE   1


#endif //CONSTANS_H