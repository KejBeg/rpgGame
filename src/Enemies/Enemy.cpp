#include "Enemies/Enemy.h"
#include "Character.h"
#include "Weapons/UnarmedWeapon.h"
#include <algorithm>
#include <iostream>

Enemy::Enemy(std::string name, uint16_t maxHealth, uint16_t bottlecaps)
    : name(std::move(name)), health(maxHealth), maxHealth(maxHealth),
      bottlecaps(bottlecaps), currentWeapon(UnarmedWeapon("Fists", 1, 100, 1)) {
}

const std::string &Enemy::getName() const { return name; }
uint16_t Enemy::getHealth() const { return health; }
uint16_t Enemy::getBottlecaps() const { return bottlecaps; }
uint16_t Enemy::getMaxHealth() const { return maxHealth; }
const Weapon &Enemy::getCurrentWeapon() const { return currentWeapon; }
Weapon &Enemy::getCurrentWeapon() { return currentWeapon; }

void Enemy::setName(const std::string &name) { this->name = name; }

void Enemy::setHealth(uint16_t health) { this->health = health; }

void Enemy::setBottlecaps(uint16_t bottlecaps) {
  this->bottlecaps = bottlecaps;
}

void Enemy::setMaxHealth(uint16_t maxHealth) { this->maxHealth = maxHealth; }

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
  int newHealth = static_cast<int>(this->health) - static_cast<int>(damage);
  if (newHealth < 0)
    newHealth = 0;
  setHealth(static_cast<uint16_t>(newHealth));
}
