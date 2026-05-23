#ifndef FIELD_H 
#define FIELD_H

#include <iostream>
#include "constans.h"
#include "Obj.h"


//=================================================
//                                           Field


class Field {
 private:

  Obj* XYnet[GRID_SIZE_X][GRID_SIZE_Y];

  bool isin(int x, int y) const;


  Field();
  Field(const Field&) = delete;
  Field& operator=(const Field&) = delete;

 public:

  static Field& get_instance();

  void set_Obj(int x, int y, Obj* obj);

  Obj* get_Obj(int x, int y) const;

  void rm_Obj(int x, int y);

  void move_Obj(int from_x, int from_y, int to_x, int to_y);

  void print_field() const; 
};

#define FIELD Field::get_instance()

#endif //FIELD_H