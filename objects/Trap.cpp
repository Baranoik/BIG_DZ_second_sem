#include "Trap.h"
#include "Log_config.h"
#include <random>

//-------------------------------------------------
//                                        Base Trap
//-------------------------------------------------
Trap::Trap() : Obj(), is_active(true) { 
  LOG("Trap() : Base trap object constructed | " << this);
}

OBJ_TYPE Trap::get_type() const {
  return OBJ_TYPE::TRAP;
}

void Trap::tick_eff() {
  Obj::tick_eff();

  is_active = !is_active;
    
  LOG("Trap::tick_eff() : Toggle activity status -> " << (is_active ? "[ACTIVE]" : "[INACTIVE]") << " | " << this);
}

bool Trap::get_active_status() const {
    return is_active;
}

//-------------------------------------------------
//                                      Spikes Trap
//-------------------------------------------------
Spikes::Spikes() : Trap() {
  std::random_device trap_rd;
  std::default_random_engine trap_gen(trap_rd());
  std::uniform_int_distribution<int> dmg_dist(3, 7);

  soundnes = dmg_dist(trap_gen);
    
  LOG("Spikes() : Created spikes | soundnes (damage): " << soundnes << " | active: " << is_active << " | " << this);
}

TRAP_TYPE Spikes::get_trap_type() const {
  return TRAP_TYPE::SPIKES;
}

int Spikes::get_spikes_damage() const {
  return soundnes; 
}

//-------------------------------------------------
//                                Flamethrower Trap
//-------------------------------------------------
Flamethrower::Flamethrower() : Trap() {
  std::random_device trap_rd;
  std::default_random_engine trap_gen(trap_rd());
    
  std::uniform_int_distribution<int> charges_dist(2, 4);
  soundnes = charges_dist(trap_gen);

  std::uniform_int_distribution<int> dur_dist(2, 4);
  burn_duration = dur_dist(trap_gen);

  LOG("Flamethrower() : Created flamethrower | soundnes (charges): " << soundnes 
    << " | burn duration: " << burn_duration << " | active: " << is_active << " | " << this);
}

TRAP_TYPE Flamethrower::get_trap_type() const {
  return TRAP_TYPE::FLAMETHROWER;
}

StatusEffect Flamethrower::get_trigger_effect() const {
  return StatusEffect(ELEMENT_TYPE::FIRE, burn_duration);
}

void Flamethrower::reduce_charges() {
  if (soundnes > 0) {
    soundnes--;
    LOG("Flamethrower::reduce_charges() : Charge used. Remaining soundnes (charges): " << soundnes << " | " << this);
  }
}