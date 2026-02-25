#include "Enemies/Enemy.h"
#include "Character.h"
#include <algorithm>
#include <iostream>


Enemy::Enemy(std::string name, int health, int bottlecaps, const Weapon &weapon)
    : name(std::move(name)), health(std::max(0, health)), bottlecaps(std::max(0, bottlecaps)),
      currentWeapon(weapon) {}

const std::string &Enemy::getName() const { return name; }
int Enemy::getHealth() const { return health; }
int Enemy::getBottlecaps() const { return bottlecaps; }
const Weapon &Enemy::getCurrentWeapon() const { return currentWeapon; }
Weapon &Enemy::getCurrentWeapon() { return currentWeapon; }

void Enemy::setName(const std::string &name) { this->name = name; }

void Enemy::setHealth(int health) { this->health = std::max(0, health); }

void Enemy::setBottlecaps(int bottlecaps) {
  this->bottlecaps = std::max(0, bottlecaps);
}

void Enemy::setCurrentWeapon(const Weapon &weapon) {
  this->currentWeapon = weapon;
}

void Enemy::attack(Character &character) {
  uint16_t totalDamage = 0;

  for (int i = 0; i < currentWeapon.getHitReps(); i++) {
    if ((std::rand() % 100) < currentWeapon.getHitChance()) {
      totalDamage += currentWeapon.getDamage();
    }
  }

  character.takeDamage(totalDamage);

  std::cout << this->getType() << " " << this->name << " attacks "
            << character.getName() << " with " << currentWeapon.getName()
            << " for " << totalDamage << " damage!" << std::endl;
}

void Enemy::takeDamage(uint16_t damage) {
  // Use setter to enforce clamping and ownership rules.
  setHealth(this->health - static_cast<int>(damage));
}
