#include <iostream>
#include "Field.h"
#include "Obj.h"
#include "Player.h"
#include "Log_config.h"

int main() {
  SETUP_BASE_COLOR;
  std::cout << "\n===  0.2 test  ===" << std::endl;
  ANCOLORING;

  Player player;
  Obj obj1;
  Obj obj2;

  std::cout << "\n   preporition"<< std::endl;
  FIELD.set_Obj(0, 0, &player); 
  FIELD.set_Obj(1, 1, &obj1);
  FIELD.set_Obj(2, 2, &obj2); 

  std::cout << "\n ---print  text---" << std::endl;
  FIELD.print_field();

  std::cout << "\n set to seted test"<< std::endl;
  FIELD.set_Obj(0, 0, &obj2); 
  FIELD.set_Obj(1, 1, &player); 

  std::cout << "\n\n--- lv up test ---" << std::endl;
  
  player.add_score(150);
  std::cout<<std::endl;
  player.lv_up();
  return 0;
}