#include "Weapons/Weapon.h"
#include <utility>

Weapon::Weapon(std::string name, uint16_t damage, uint8_t hitChance, uint8_t hitReps) {
  this->name = std::move(name);
  this->damage = damage;
  this->hitChance = hitChance;
  this->hitReps = hitReps;
}

std::string Weapon::getName() const { return name; }

uint16_t Weapon::getDamage() const { return damage; }

uint8_t Weapon::getHitChance() const { return hitChance; }

uint8_t Weapon::getHitReps() const { return hitReps; }

void Weapon::setName(std::string name) { this->name = std::move(name); }

void Weapon::setDamage(uint16_t damage) { this->damage = damage; }

void Weapon::setHitChance(uint8_t hitChance) { this->hitChance = hitChance; }

void Weapon::setHitReps(uint8_t hitReps) { this->hitReps = hitReps; }
