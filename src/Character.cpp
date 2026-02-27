#include "Character.h"
#include "Enemies/Enemy.h"
#include <algorithm>
#include <cstdlib>
#include <iostream>

Character::Character(std::string name, uint16_t maxHealth, uint16_t bottlecaps,
                     std::list<Weapon> weaponList) {
  this->name = name;
  this->health = maxHealth;
  this->maxHealth = maxHealth;
  this->bottlecaps = bottlecaps;
  this->weaponList = weaponList;
}

const std::string &Character::getName() const { return name; }
uint16_t Character::getHealth() const { return health; }
uint16_t Character::getBottlecaps() const { return bottlecaps; }
uint16_t Character::getMaxHealth() const { return maxHealth; }
const std::list<Weapon> &Character::getWeaponList() const { return weaponList; }
std::list<Weapon> &Character::getWeaponList() { return weaponList; }

void Character::setName(const std::string &name) { this->name = name; }
void Character::setHealth(uint16_t health) {
  // clamp to [0, maxHealth]
  if (health > maxHealth) {
    this->health = maxHealth;
  } else {
    this->health = health;
  }
}
void Character::setBottlecaps(uint16_t bottlecaps) { this->bottlecaps = bottlecaps; }

void Character::setMaxHealth(uint16_t maxHealth) { this->maxHealth = maxHealth; }
void Character::setWeaponList(const std::list<Weapon> &weaponList) {
  this->weaponList = weaponList;
}

void Character::takeDamage(uint16_t damage) {
  int newHealth = static_cast<int>(health) - static_cast<int>(damage);
  if (newHealth < 0) newHealth = 0;
  setHealth(static_cast<uint16_t>(newHealth));
  std::cout << name << " takes " << damage
            << " damage! Current health: " << health << std::endl;
}

void Character::attack(Enemy &enemy, const Weapon &weapon) {
  uint16_t totalDamage = 0;

  for (int i = 0; i < weapon.getHitReps(); i++) {
    if ((std::rand() % 100) < weapon.getHitChance()) {
      totalDamage += weapon.getDamage();
    }
  }

  enemy.takeDamage(totalDamage);

  std::cout << this->name << " attacks " << enemy.getType() << " "
            << enemy.getName() << " with " << weapon.getName() << " for "
            << totalDamage << " damage!" << std::endl;
}
