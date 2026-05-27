#ifndef INTERACTION_SYS_H
#define INTERACTION_SYS_H

#include "Field.h"
#include "Obj.h"

class Interaction_sys {
private:
  Interaction_sys() = default;
  Interaction_sys(const Interaction_sys&) = delete;
  Interaction_sys& operator=(const Interaction_sys&) = delete;

  void handle_chest(Obj* initiator, Obj* target, int x, int y);
  void handle_reward(Obj* initiator, Obj* target, int x, int y);
  void handle_trap(Obj* initiator, Obj* target, int x, int y);
  void handle_battle(Obj* initiator, Obj* target, int x, int y);

public:
  static Interaction_sys& get_instance();

  void process_step(Obj* initiator, int from_x, int from_y, int to_x, int to_y);
};

#define INTERACT Interaction_sys::get_instance()

#endif // INTERACTION_SYS_H
