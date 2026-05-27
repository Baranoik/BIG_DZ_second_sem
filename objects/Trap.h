#ifndef TRAP_H
#define TRAP_H

#include "Obj.h"
#include "element.h"

enum class TRAP_TYPE {
  SPIKES,
  FLAMETHROWER
};

//=================================================
//                                        Base Trap
class Trap : public Obj {
protected:
  bool is_active; // Модификатор: активна ли ловушка прямо сейчас

public:
  Trap();
  ~Trap() override = default;

  OBJ_TYPE get_type() const override;
    
  void tick_eff() override;

  virtual TRAP_TYPE get_trap_type() const = 0;
    
  bool get_active_status() const;
};

//=================================================
//                                      Spikes Trap
class Spikes : public Trap {
public:
  Spikes();
  ~Spikes() override = default;

  TRAP_TYPE get_trap_type() const override;
    
  int get_spikes_damage() const;
};

//=================================================
//                                Flamethrower Trap
class Flamethrower : public Trap {
private:
  int burn_duration;

public:
  Flamethrower();
  ~Flamethrower() override = default;

  TRAP_TYPE get_trap_type() const override;
  StatusEffect get_trigger_effect() const;
  void reduce_charges();
};

#endif // TRAP_H