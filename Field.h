#include <iostream>
#include "constans.h"
#include "Obj.h"


//=================================================
//                                           Field


class Field {
 private:

  Obj* matrix[GRID_SIZE_Y][GRID_SIZE_X] = { nullptr } XYnet;

  bool isin(int x, int y) const {};


  Field() {};
  Field(const Field&) = delete;
  Field& operator=(const Field&) = delete;

 public:

  static Field& get_instance() {};

  void placeObject(int x, int y, Obj* obj) {};

  Obj* get_Obj(int x, int y) const {};
};

#define FIELD Field::get_instance()