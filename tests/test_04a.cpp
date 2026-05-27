#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <string>
#include <optional> // Для работы с std::optional в SFML 3

#include "Field.h"
#include "objects/Player.h"
#include "objects/Entity.h"
#include "objects/Reward.h"
#include "objects/Chest.h"
#include "objects/Trap.h"
#include "Interaction_sys.h"
#include "Obj_manager.h"
#include "Render.h"
#include "Log_config.h"

struct TestAction {
    std::string description;
    int from_x, from_y;
    int to_x, to_y;
};

int main() {
    // 1. Инициализация окна в стиле SFML 3 (передача размеров через фигурные скобки {})
    sf::RenderWindow window(sf::VideoMode({600, 600}), "SFML 3 Graphics & Action Test");
    window.setFramerateLimit(60);

    if (!RENDER.init("Front.ttf")) {
        std::cout << "Пожалуйста, положите файл шрифта arial.ttf в папку с проектом!" << std::endl;
        return -1;
    }

    // 2. Расстановка объектов на поле 3х3
    Player* player = new Player();
    FIELD.set_Obj(1, 1, player); 

    StatusEffect burn_test(ELEMENT_TYPE::FIRE, 3);
    player->apply_eff(burn_test);

    Spikes* spikes = new Spikes();
    FIELD.set_Obj(0, 1, spikes); 

    Chest* chest = new Chest();
    FIELD.set_Obj(1, 0, chest);  

    Skeleton* skel = new Skeleton();
    skel->set_soundness(5);
    FIELD.set_Obj(1, 2, skel);   

    Coin* coin = new Coin();
    FIELD.set_Obj(2, 1, coin);   

    // 3. Очередь автоматических действий
    std::vector<TestAction> script = {
        {"Игрок наступает на ШИПЫ (вверх на {0;1})", 1, 1, 0, 1},
        {"Игрок возвращается (вверх на {0;1})", 1, 1, 1, 1},
        {"Игрок бьет СУНДУК (влево на {1;0})", 1, 1, 1, 0},
        {"Игрок атакует СКЕЛЕТА оружием (вправо на {1;2})", 1, 1, 1, 2},
        {"Игрок идет подбирать МОНЕТУ (вниз на {2;1})", 1, 1, 2, 1},
        {"Игрок просто пропускает ход (стоит на месте)", 1, 1, 1, 1},
        {"Игрок подбирает оружие (влево на {1;0})", 1, 1, 1, 0}

    };

    size_t current_step = 0;
    sf::Clock clock;
    float time_per_step = 1.5f; 

    std::cout << "Запуск визуального теста SFML " << std::endl;

    // 4. Главный цикл отображения
    while (window.isOpen()) {
        
        // Обработка событий в стиле SFML 3 (через std::optional и метод ->is)
        while (const std::optional<sf::Event> event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
        }

        // Логика автоматических шагов по таймеру
        if (current_step < script.size() && clock.getElapsedTime().asSeconds() >= time_per_step) {
            clock.restart(); 

            TestAction action = script[current_step];
            std::cout << "\n[ШАГ ТЕСТА " << (current_step + 1) << "]: " << action.description << std::endl;

            int actual_x = -1, actual_y = -1;
            for (int x = 0; x < GRID_SIZE_X; ++x) {
                for (int y = 0; y < GRID_SIZE_Y; ++y) {
                    if (FIELD.get_Obj(x, y) == player) {
                        actual_x = x; actual_y = y;
                    }
                }
            }

            if (actual_x != -1 && actual_y != -1) {
                INTERACT.process_step(player, actual_x, actual_y, action.to_x, action.to_y);
            } else {
                std::cout << "[ВНИМАНИЕ] Игрок не найден на поле!" << std::endl;
            }

            OBJ_MGR.tick_all_eff();
            OBJ_MGR.cleanup_dead_objects();

            current_step++;
        }

        // Отрисовка
        window.clear(sf::Color::Black);
        RENDER.draw_all(window, player);
        window.display();
    }

    OBJ_MGR.clear_field();
    return 0;
}
