#include <iostream>
#include "Field.h"
#include "Player.h"
#include "Entity.h"
#include "Reward.h"
#include "Chest.h"
#include "Interaction_sys.h"
#include "Obj_manager.h"
#include "Log_config.h"

// Вспомогательная функция для прогона конца хода без геймлоджика
void end_of_turn() {
    OBJ_MGR.tick_all_eff();
    OBJ_MGR.cleanup_dead_objects();
    FIELD.print_field();
}

int main() {
    SETUP_BASE_COLOR;
    std::cout << "\n=== Test 04: Pure Interaction System & Combat Test ===\n" << std::endl;
    ANCOLORING;

    // Инициализируем игрока. Стартовый урон оружия = 11. HP = 10.
    Player* player = new Player();
    FIELD.set_Obj(1, 1, player); // Игрок на {1;1}
    
    std::cout << "\n--- Scenario 1: Combat WITH Weapon ---" << std::endl;
    Skeleton* weak_skel = new Skeleton();
    weak_skel->set_soundness(5); 
    FIELD.set_Obj(0, 1, weak_skel); // Скелет СВЕРХУ {0;1}

    std::cout << "Initial Weapon Perf: " << player->get_weapon_damage() << std::endl;
    FIELD.print_field();

    // Игрок пытается атаковать вверх (с {1;1} на {0;1})
    INTERACT.process_step(player, 1, 1, 0, 1);
    end_of_turn();

    std::cout << "\nResult Scenario 1:" << std::endl;
    std::cout << "Weapon Perf after fight (expected 11 - 5 = 6): " << player->get_weapon_damage() << std::endl;
    std::cout << "Player Position (expected to stay at {1;1} due to weapon combat rule):" << std::endl;


    std::cout << "\n--- Scenario 2: Combat WITHOUT Weapon (Bare Hands) ---" << std::endl;
    // Ломаем оружие игрока в 0
    player->damage_weapon(player->get_weapon_damage()); 
    std::cout << "Weapon Perf now: " << player->get_weapon_damage() << " (Hands Mode ACTIVE)" << std::endl;

    // Спавним нового скелета СВЕРХУ {0;1}
    Skeleton* hand_skel = new Skeleton();
    hand_skel->set_soundness(4); 
    FIELD.set_Obj(0, 1, hand_skel);
    FIELD.print_field();

    // Игрок бьет руками вверх (с {1;1} на {0;1})
    INTERACT.process_step(player, 1, 1, 0, 1);
    end_of_turn();

    std::cout << "\nResult Scenario 2:" << std::endl;
    std::cout << "Player HP after fight (expected 10 - 4 = 6): " << player->get_hp() << std::endl;
    std::cout << "Player Position (expected to step on {0;1} automatically, no loot):" << std::endl;


    std::cout << "\n--- Scenario 3: Stepping on a Potion (Reward) ---" << std::endl;
    // Спавним зелье на клетке {0;2} (справа от текущей позиции игрока {0;1})
    Potion* test_potion = new Potion(ELEMENT_TYPE::FIRE);
    FIELD.set_Obj(0, 2, test_potion);
    FIELD.print_field();

    // Игрок идет вправо (с {0;1} на {0;2})
    INTERACT.process_step(player, 0, 1, 0, 2);
    end_of_turn();

    std::cout << "\nResult Scenario 3:" << std::endl;
    std::cout << "Player Position (expected to absorb potion and step on cell {0;2}):" << std::endl;


    std::cout << "\n--- Scenario 4: Hit a Chest ---" << std::endl;
    // Спавним сундук снизу {1;2} (под игроком {0;2})
    Chest* test_chest = new Chest();
    FIELD.set_Obj(1, 2, test_chest);
    FIELD.print_field();

    // Игрок атакует сундук вниз (с {0;2} на {1;2})
    INTERACT.process_step(player, 0, 2, 1, 2);
    end_of_turn();

    std::cout << "\nResult Scenario 4:" << std::endl;
    std::cout << "Player Position (expected to stay on {0;2}, chest replaced by reward on {1;2}):" << std::endl;

    // Очищаем всё поле
    OBJ_MGR.clear_field();
    std::cout << "\n=== Test 04 Finished Successfully ===" << std::endl;
    return 0;
}
