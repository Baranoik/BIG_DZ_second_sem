#include "Render.h"
#include "Log_config.h"
#include "element.h" // Подключаем, чтобы рендерер знал типы ELEMENT_TYPE

// Добавляем инклюды объектов для безопасного чтения их уникальных статов
#include "objects/Reward.h"
#include "objects/Trap.h"
#include "objects/Entity.h"

Render_Sys::Render_Sys() : cell_text(nullptr), ui_text(nullptr), sub_text(nullptr), effbar_text(nullptr) {
    // Конструктор оставляем пустым, так как шрифт еще не загружен
}

Render_Sys::~Render_Sys() {
    if (cell_text) delete cell_text;
    if (ui_text) delete ui_text;
    if (sub_text) delete sub_text;
    if (effbar_text) delete effbar_text;
}

Render_Sys& Render_Sys::get_instance() {
    static Render_Sys instance;
    return instance;
}

bool Render_Sys::init(const std::string& font_path) {
    if (!font.openFromFile(font_path)) {
        return false;
    }
    
    cell_text = new sf::Text(font, "", 40);
    ui_text = new sf::Text(font, "", 20);
    
    sub_text = new sf::Text(font, "", 14); 
    sub_text->setFillColor(sf::Color(180, 180, 180)); // Светло-серый
    
    effbar_text = new sf::Text(font, "", 12);
    effbar_text->setFillColor(sf::Color(255, 165, 0));
    
    ui_text->setFillColor(sf::Color::White);
    return true;
}

void Render_Sys::draw_all(sf::RenderWindow& window, Player* player) {
    if (!cell_text || !ui_text || !sub_text || !effbar_text) return;

    if (player != nullptr) {
        std::string ui_str = "SCORE: " + std::to_string(player->get_score()) +
                             " | LVL: " + std::to_string(player->get_level());
        
        if (player->isdead()) {
            ui_str += "  --- GAME OVER ---";
        }

        ui_text->setString(ui_str);
        ui_text->setPosition({200.0f, 50.0f});
        window.draw(*ui_text);
    } else {
        ui_text->setString("SCORE: -- | LVL: --  --- GAME OVER ---");
        ui_text->setPosition({30.0f, 50.0f});
        window.draw(*ui_text);
    }

    for (int x = 0; x < GRID_SIZE_X; ++x) {
        for (int y = 0; y < GRID_SIZE_Y; ++y) {
            
            float custom_cell_size = 130.0f;
            float screen_x = offset_x + y * custom_cell_size;
            float screen_y = offset_y + x * 145.0f; 

            Obj* obj = FIELD.get_Obj(x, y);

            std::string sub_str = ""; 
            std::string effbar_str = "";

            if (obj == nullptr) {
                cell_text->setString("[ . ]");
                cell_text->setFillColor(sf::Color(120, 120, 120)); 
            } else {
                // Читаем вектор эффектов из созданной функции для любого живого объекта
                std::vector<ELEMENT_TYPE> eff_types = obj->get_status_types();
                if (!eff_types.empty()) {
                    effbar_str = "Eff:";
                    for (auto t : eff_types) {
                        switch (t) {
                            case ELEMENT_TYPE::FIRE:        effbar_str += " [Fr]"; break;
                            case ELEMENT_TYPE::POISON:      effbar_str += " [Ps]"; break;
                            case ELEMENT_TYPE::ICE:         effbar_str += " [Ic]"; break;
                            case ELEMENT_TYPE::REGENRATION: effbar_str += " [Rg]"; break;
                            default: break;
                        }
                    }
                }

                switch (obj->get_type()) {
                    case OBJ_TYPE::PLAYER: {
                        cell_text->setString("[ @ ]"); 
                        cell_text->setFillColor(sf::Color::Green); 
                        
                        // Безопасно вытягиваем данные живого игрока, переданного в метод draw_all
                        if (player != nullptr) {
                            sub_str = "HP " + std::to_string(player->get_hp()) + "/" + std::to_string(player->get_max_hp()) 
                                      + (player->has_weapon() ? (" :" + std::to_string(player->get_weapon_damage())) : " :X");
                        } else {
                            sub_str = "HP: DEAD";
                        }
                        break;
                    }
                    case OBJ_TYPE::CHEST: {
                        cell_text->setString("[ C ]"); 
                        cell_text->setFillColor(sf::Color::Yellow); 
                        sub_str = "HP: " + std::to_string(obj->get_soundness());
                        break;
                    }
                    case OBJ_TYPE::ENTITY: {
                        cell_text->setString("[ E ]"); 
                        cell_text->setFillColor(sf::Color::Magenta); 
                        sub_str = "HP: " + std::to_string(obj->get_soundness());
                        break;
                    }
                    case OBJ_TYPE::TRAP: {
                        cell_text->setString("[ T ]"); 
                        cell_text->setFillColor(sf::Color::Red); 
                        
                        Trap* trap = dynamic_cast<Trap*>(obj);
                        if (trap) {
                            std::string state = trap->get_active_status() ? "ON" : "OFF";
                            if (trap->get_trap_type() == TRAP_TYPE::SPIKES) {
                                sub_str = "Spikes:" + state;
                            } else if (trap->get_trap_type() == TRAP_TYPE::FLAMETHROWER) {
                                sub_str = "Flm:" + state + "(" + std::to_string(trap->get_soundness()) + ")";
                            }
                        }
                        break;
                    }
                    case OBJ_TYPE::REVARD: {
                        cell_text->setString("[ R ]"); 
                        cell_text->setFillColor(sf::Color::Cyan); 
                        
                        Reward* reward = dynamic_cast<Reward*>(obj);
                        if (reward) {
                            switch (reward->get_reward_type()) {
                                case REWARD_TYPE::COIN:   sub_str = "Coin:" + std::to_string(reward->get_soundness()); break;
                                case REWARD_TYPE::WEAPON: sub_str = "Weapon: " + std::to_string(reward->get_soundness()); break;
                                case REWARD_TYPE::POTION: sub_str = "Potion: " + std::to_string(reward->get_soundness()); break;
                            }
                        }
                        break;
                    }
                    default: {
                        cell_text->setString("[ ? ]"); 
                        cell_text->setFillColor(sf::Color::White); 
                        break;
                    }
                }
            }

            // 1 строчка: Крупный символ клетки (шрифт 40)
            cell_text->setPosition({screen_x, screen_y});
            window.draw(*cell_text);

            // 2 строчка: Мелкое описание (HP, Статус ловушки, Название награды) — смещено на 55px вниз
            if (!sub_str.empty()) {
                sub_text->setString(sub_str);
                sub_text->setPosition({screen_x + 5.0f, screen_y + 55.0f});
                window.draw(*sub_text);
            }

            // 3 строчка: Статус-эффекты объекта (выводится на 75 пикселей ниже начала клетки)
            if (!effbar_str.empty()) {
                effbar_text->setString(effbar_str);
                effbar_text->setPosition({screen_x + 5.0f, screen_y + 75.0f});
                window.draw(*effbar_text);
            }
        }
    }
}
