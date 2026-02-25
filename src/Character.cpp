#include "Character.h"
#include "Enemies/Enemy.h"
#include <algorithm>
#include <cstdlib>
#include <iostream>

Character::Character(std::string name, int health, int bottlecaps,
                     std::list<Weapon> weaponList) {
  this->name = name;
  setHealth(health);
  setBottlecaps(bottlecaps);
  this->weaponList = weaponList;
}

const std::string &Character::getName() const { return name; }
int Character::getHealth() const { return health; }
int Character::getBottlecaps() const { return bottlecaps; }
const std::list<Weapon> &Character::getWeaponList() const { return weaponList; }
std::list<Weapon> &Character::getWeaponList() { return weaponList; }

void Character::setName(const std::string &name) { this->name = name; }
void Character::setHealth(int health) {
  if (health < 0) {
    this->health = 0;
  } else {
    this->health = health;
  }
}
void Character::setBottlecaps(int bottlecaps) {
  this->bottlecaps = std::max(0, bottlecaps);
}
void Character::setWeaponList(const std::list<Weapon> &weaponList) {
  this->weaponList = weaponList;
}

void Character::takeDamage(uint16_t damage) {
  setHealth(health - damage);
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
