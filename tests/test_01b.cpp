#include <iostream>
#include "Field.h"
#include "Obj.h"
#include "Log_config.h"

int main() {
  ANCOLORING
  std::cout << "\n\n=== Test 0.1b ===\n" << std::endl;
  ANCOLORING;

  Obj obj1;
  Obj obj2;
  Obj obj3;
  Obj obj4;
  Obj obj5;

  std::cout << "\n   obj -> Field  \n" << std::endl;
    
    
  FIELD.set_Obj(2, 0, &obj1); 
  FIELD.set_Obj(0, 1, &obj2); 
  FIELD.set_Obj(1, 1, &obj3); 
  FIELD.set_Obj(1, 2, &obj4);
  FIELD.set_Obj(1, 2, &obj5);
    
  FIELD.print_field();

  std::cout << "\n     get_Obj \n" << std::endl;
  FIELD.get_Obj(1, 1);
  FIELD.get_Obj(5, 5);


  std::cout << "\n   Error test" << std::endl;
    
  FIELD.set_Obj(9, 9, &obj1); 

  std::cout << "Этот текст никогда не выведется - потому и на руском)))" << std::endl;
  return 0;
}
