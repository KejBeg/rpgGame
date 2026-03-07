#include "Weapons/Weapon.h"
#include <utility>

////////////////////
/// Constructors ///
////////////////////

Weapon::Weapon(uint16_t id, std::string name, uint16_t damage, uint8_t hitChance,
               uint8_t hitReps) {
  this->id = id;
  this->name = std::move(name);
  this->damage = damage;
  this->hitChance = hitChance;
  this->hitReps = hitReps;
}

Weapon::Weapon() : id(0), name(""), damage(0), hitChance(0), hitReps(0) {}

///////////////
/// Getters ///
///////////////

uint16_t Weapon::getId() const { return id; }

std::string Weapon::getName() const { return name; }

uint16_t Weapon::getDamage() const { return damage; }

uint8_t Weapon::getHitChance() const { return hitChance; }

uint8_t Weapon::getHitReps() const { return hitReps; }

///////////////
/// Setters ///
///////////////

void Weapon::setId(uint16_t id) { this->id = id; }

void Weapon::setName(std::string name) { this->name = std::move(name); }

void Weapon::setDamage(uint16_t damage) { this->damage = damage; }

void Weapon::setHitChance(uint8_t hitChance) { this->hitChance = hitChance; }

void Weapon::setHitReps(uint8_t hitReps) { this->hitReps = hitReps; }

////////////////
//// Methods ///
////////////////

std::string Weapon::getType() const { return "Weapon"; }
