#include <iostream>
#include <vector>
#include "Obj.h"
#include "element.h"
#include "Log_config.h"

int main() {
    SETUP_BASE_COLOR;
    std::cout << "\n=== test_02b (effect test) ===" << std::endl;
    ANCOLORING;

    Obj* test_dummy = new Obj();

    StatusEffect fire(ELEMENT_TYPE::FIRE, BURN_DURATION, BURN_DAMAGE);
    StatusEffect poison(ELEMENT_TYPE::POISON, POISON_DURATION, POISON_DAMAGE);

    std::cout << "\n--- Applying Effects ---" << std::endl;
    test_dummy->apply_eff(fire);
    test_dummy->apply_eff(poison);

    StatusEffect weak_fire(ELEMENT_TYPE::FIRE, 1, BURN_DAMAGE);
    test_dummy->apply_eff(weak_fire);

    std::cout << "\n--- Simulating Turns ---" << std::endl;
    for (int turn = 1; turn <= 4; ++turn) {
        std::cout << "\n[ Turn " << turn << " ]" << std::endl;
        
        std::vector<std::string> bar = test_dummy->get_eff_bar();
        std::cout << "Active Eff Bar content:" << std::endl;
        for (const auto& line : bar) {
            std::cout << "  " << line << std::endl;
        }

        test_dummy->tick_eff();
    }

    delete test_dummy;

    ANCOLORING;
    return 0;
}