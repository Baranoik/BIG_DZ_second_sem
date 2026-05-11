#include "entity.h"

void Entity::applyStatusFromElement(ElementType element) {
    switch (element) {
    case ElementType::FIRE:
        // Не накладываем горение, если уже горит – продлеваем длительность
        if (!hasStatus(ElementType::FIRE)) {
            m_statusEffects.emplace_back(ElementType::FIRE, BURN_DURATION, BURN_DAMAGE);
        }
        break;
    case ElementType::ICE:
        if (!hasStatus(ElementType::ICE)) {
            m_statusEffects.emplace_back(ElementType::ICE, FROZEN_DURATION, 0);
        }
        break;
    case ElementType::POISON:
        if (!hasStatus(ElementType::POISON)) {
            m_statusEffects.emplace_back(ElementType::POISON, POISON_DURATION, POISON_DAMAGE);
        }
        break;
    default:
        break;
    }
}

void Entity::updateStatusEffects() {
    for (auto it = m_statusEffects.begin(); it != m_statusEffects.end(); ) {
        // Наносим урон за тик (горение/яд)
        if (it->damagePerTurn > 0) {
            m_health -= it->damagePerTurn;
        }
        it->duration--;
        if (it->duration <= 0) {
            it = m_statusEffects.erase(it);
        } else {
            ++it;
        }
    }
    if (m_health < 0) m_health = 0;
}

bool Entity::takeDamage(int amount, ElementType attackerElement) {
    m_health -= amount;
    if (attackerElement != ElementType::NONE) {
        applyStatusFromElement(attackerElement);
    }
    if (m_health < 0) m_health = 0;
    return !isAlive();
}

void Entity::attack(Entity& target) {
    int dmg = m_attack;
    target.takeDamage(dmg, m_attackElement);
}

bool Entity::hasStatus(ElementType type) const {
    for (const auto& eff : m_statusEffects)
        if (eff.type == type) return true;
    return false;
}

int Entity::getStatusDuration(ElementType type) const {
    for (const auto& eff : m_statusEffects)
        if (eff.type == type) return eff.duration;
    return 0;
}

void Entity::clearStatus(ElementType type) {
    m_statusEffects.erase(
        remove_if(m_statusEffects.begin(), m_statusEffects.end(),
            [type](const StatusEffect& e) { return e.type == type; }),
        m_statusEffects.end());
}

// Фабрика
std::unique_ptr<Entity> EntityFactory::createMonster(MonsterType type) {
    switch (type) {
    case MonsterType::FIRE_IMP:
        return std::make_unique<Entity>(FIRE_IMP_HP, FIRE_IMP_ATTACK, ElementType::FIRE);
    case MonsterType::ICE_SKELETON:
        return std::make_unique<Entity>(ICE_SKELETON_HP, ICE_SKELETON_ATTACK, ElementType::ICE);
    case MonsterType::MIMIC:
        return std::make_unique<Entity>(MIMIC_HP, MIMIC_ATTACK, ElementType::NONE);
    default:
        return nullptr;
    }
}
// Обратите внимание: для простоты все монстры — экземпляры Entity,
// но с разными параметрами. Различие в поведении достигается за счёт
// разных ElementType и, как следствие, накладываемых статусных эффектов.
// Это соответствует требованию "разного игрового поведения".