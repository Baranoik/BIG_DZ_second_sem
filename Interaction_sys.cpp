#include "Interaction_sys.h"
#include "Log_config.h"
#include "Player.h"
#include "Chest.h"
#include "Reward.h"
#include "Trap.h"
#include "Entity.h"
#include "Obj_fabric.h" 
#include <algorithm> // Для std::min

Interaction_sys& Interaction_sys::get_instance() {
  static Interaction_sys instance;
  return instance;
}

void Interaction_sys::process_step(Obj* initiator, int from_x, int from_y, int to_x, int to_y) {
  if (initiator == nullptr) return;
  
  if (!FIELD.isin(to_x, to_y)) {
    LOG("[Interaction_sys] Action out of bounds ignored.");
    return;
  }

  Obj* target = FIELD.get_Obj(to_x, to_y);

  if (target == nullptr) {
    FIELD.move_Obj(from_x, from_y, to_x, to_y);
    return;
  }

  switch (target->get_type()) {
    case OBJ_TYPE::CHEST:
      handle_chest(initiator, target, to_x, to_y);
      break;
    case OBJ_TYPE::REVARD:
      handle_reward(initiator, target, to_x, to_y);
      FIELD.move_Obj(from_x, from_y, to_x, to_y);
      break;
    case OBJ_TYPE::TRAP:
      handle_trap(initiator, target, to_x, to_y);
      FIELD.move_Obj(from_x, from_y, to_x, to_y);
      break;
    case OBJ_TYPE::ENTITY:
      handle_battle(initiator, target, to_x, to_y);
      break;
    default:
      LOG("[Interaction_sys] Unknown interaction target type.");
      break;
  }
}

void Interaction_sys::handle_chest(Obj* initiator, Obj* target, int x, int y) {
  if (initiator->get_type() == OBJ_TYPE::PLAYER) {
    LOG("[Interaction_sys] Player breaks the chest!");
    FIELD.rm_Obj(x, y);
    Obj* reward = FABRIC.create_random_reward();
    FIELD.set_Obj(x, y, reward);
  }
}

void Interaction_sys::handle_reward(Obj* initiator, Obj* target, int x, int y) {
  if (initiator->get_type() != OBJ_TYPE::PLAYER) return;
  
  Player* player = dynamic_cast<Player*>(initiator);
  Reward* reward = dynamic_cast<Reward*>(target);
  if (!player || !reward) return;

  switch (reward->get_reward_type()) {
    case REWARD_TYPE::COIN: {
      Coin* c = dynamic_cast<Coin*>(reward);
      player->add_score(c->get_gold_amount());
      break;
    }
    case REWARD_TYPE::POTION: {
      Potion* p = dynamic_cast<Potion*>(reward);
      player->apply_eff(p->get_effect());
      break;
    }
    case REWARD_TYPE::WEAPON: {
      Weapon* w = dynamic_cast<Weapon*>(reward);
      if (w->get_elemental_type() != ELEMENT_TYPE::NONE) {
        player->apply_eff(w->get_weapon_effect());
      }
      player->add_score(w->get_damage_performance());
      break;
    }
  }
  FIELD.rm_Obj(x, y);
}

void Interaction_sys::handle_trap(Obj* initiator, Obj* target, int x, int y) {
  Trap* trap = dynamic_cast<Trap*>(target);
  if (!trap || !trap->get_active_status()) return;

  LOG("[Interaction_sys] Object " << initiator << " triggered an active trap!");

  if (trap->get_trap_type() == TRAP_TYPE::SPIKES) {
    Spikes* s = dynamic_cast<Spikes*>(trap);
    initiator->modify_soundness(-s->get_spikes_damage());
  } 
  else if (trap->get_trap_type() == TRAP_TYPE::FLAMETHROWER) {
    Flamethrower* f = dynamic_cast<Flamethrower*>(trap);
    initiator->apply_eff(f->get_trigger_effect());
    f->reduce_charges();
  }
}

void Interaction_sys::handle_battle(Obj* initiator, Obj* target, int x, int y) {
  if (initiator->get_type() == OBJ_TYPE::PLAYER && target->get_type() == OBJ_TYPE::ENTITY) {
    Player* player = dynamic_cast<Player*>(initiator);
    Enemy* enemy = dynamic_cast<Enemy*>(target);
    if (!player || !enemy) return;

    int enemy_hp = enemy->get_soundness();

    // Вариант А: С оружием
    if (player->has_weapon()) {
      int weapon_perf = player->get_weapon_damage();
      int final_dmg = std::min(weapon_perf, enemy_hp);
      
      enemy->modify_soundness(-final_dmg);
      player->damage_weapon(final_dmg);
      
      LOG("[Battle] Player attacks with weapon! Dealt: " << final_dmg);

      if (!enemy->isdead()) {
        int enemy_counter_dmg = enemy->get_soundness();
        player->modify_soundness(-enemy_counter_dmg);
        player->apply_eff(enemy->get_attack_effect());
        LOG("[Battle] Enemy counters Player! Dealt: " << enemy_counter_dmg);
      } else {
        LOG("[Battle] Enemy killed by weapon.");
        
        LootInfo loot = enemy->get_loot_info();
        if (loot.has_loot) {
          LOG("[Battle] Enemy drop destroyed (Spawn disabled by rules).");
        }
        
        FIELD.rm_Obj(x, y); 
      }
    } 
    // Вариант Б: Руками
    else {
      int player_hp = player->get_soundness();
      int final_dmg = std::min(player_hp, enemy_hp);

      enemy->modify_soundness(-final_dmg);
      player->modify_soundness(-final_dmg); 
      LOG("[Battle] Player attacks with bare hands! Mutual damage dealt: " << final_dmg);

      if (!enemy->isdead()) {
        player->apply_eff(enemy->get_attack_effect());
        LOG("[Battle] Enemy survives and infects Player with status effects!");
      } else {
        LOG("[Battle] Enemy killed by hands. No loot spawned.");
        int from_x = -1, from_y = -1;
        for (int gx = 0; gx < GRID_SIZE_X; ++gx) {
          for (int gy = 0; gy < GRID_SIZE_Y; ++gy) {
            if (FIELD.get_Obj(gx, gy) == player) { from_x = gx; from_y = gy; break; }
          }
        }
        
        FIELD.rm_Obj(x, y); 
        if (from_x != -1 && from_y != -1) {
          FIELD.move_Obj(from_x, from_y, x, y); 
        }
      }
    }
  }
}

