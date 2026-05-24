#include "Obj.h"
#include "Log_config.h"

Obj::Obj() : soundnes(0) {
  LOG("Obj() : " << this);
}
Obj::~Obj() {
  LOG("~Obj : " << this);
}

bool Obj::isdead() {
  return soundnes <= 0;
}

OBJ_TYPE Obj::get_type() const {
  return OBJ_TYPE::OBJ; 
}

int Obj::get_soundness() const {
  return soundnes;
}

void Obj::set_soundness(int val) {
  soundnes = val;
}

void Obj::modify_soundness(int amount) {
  soundnes += amount;
  LOG("modify_soundness() : Delta: " << amount << " | New soundness: " << soundnes << " | " << this);
}

void Obj::apply_eff(const StatusEffect& eff) {
  for (auto& current_eff : eff_bar) {
    if (current_eff.type == eff.type) {
      if (eff.duration > current_eff.duration) {
        current_eff.duration = eff.duration; 
      }
      LOG("apply_eff() : Effect extended. Dur: " << current_eff.duration);
      return;
    }
  }
  eff_bar.push_back(eff);
  LOG("apply_eff() : New effect applied. Type: " << int(eff.type) << " | Dur: " << eff.duration);
}

void Obj::tick_eff() {
  for (size_t i = 0; i < eff_bar.size(); ) {
    if (eff_bar[i].damage > 0) {
      // Наносим урон через инкапсулированный метод (урон — вычитание, передаем со знаком минус)
      modify_soundness(-eff_bar[i].damage);
    } else if (eff_bar[i].damage < 0) {
      // Если урон отрицательный (регенерация/лечение), инвертируем знак для лечения
      modify_soundness(-eff_bar[i].damage); 
    }

    eff_bar[i].duration--;

    if (eff_bar[i].duration <= 0) {
      LOG("tick_eff() : Effect expired. Type: " << int(eff_bar[i].type));
      eff_bar.erase(eff_bar.begin() + i); 
    } else {
      ++i;
    }
  }
}

std::vector<std::string> Obj::get_eff_bar() const {
  if (eff_bar.empty()) {
    LOG("get_eff_bar() : [No Effects]"); 
    return std::vector<std::string>{"[No Effects]"};
  }
  LOG("get_eff_bar() : Effects list : " << this); 
  std::vector<std::string> mesege;
  for (const auto& eff : eff_bar) {
    LOG("\t\t" << eff.get_title() + " :" + std::to_string(eff.duration));
    mesege.push_back(eff.get_title() + " :" + std::to_string(eff.duration));
  }
  return mesege;
}
