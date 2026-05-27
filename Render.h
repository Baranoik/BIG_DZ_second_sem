#ifndef RENDER_H
#define RENDER_H

#include <SFML/Graphics.hpp>
#include "Field.h"
#include "objects/Player.h"
#include "element.h"

class Render_Sys {
private:
    sf::Font font;
    
    sf::Text* cell_text;
    sf::Text* ui_text;
    sf::Text* sub_text;
    sf::Text* effbar_text; 
    
    const float cell_size = 120.0f; 
    const float offset_x = 120.0f;  
    const float offset_y = 120.0f; 

    Render_Sys();
    
public:
    static Render_Sys& get_instance();
    ~Render_Sys(); 
    
    bool init(const std::string& font_path);
    void draw_all(sf::RenderWindow& window, Player* player);
};

#define RENDER Render_Sys::get_instance()

#endif // RENDER_H
