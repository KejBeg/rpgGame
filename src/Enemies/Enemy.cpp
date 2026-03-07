#include "Enemies/Enemy.h"
#include "MainCharacter.h"
#include "Weapons/UnarmedWeapon.h"
#include <algorithm>
#include <iostream>
#include <sstream>
#include <vector>

Enemy::Enemy(std::string name, uint16_t maxHealth, uint16_t bottlecaps)
    : BaseCharacter(std::move(name), maxHealth, bottlecaps),
      currentWeapon(UnarmedWeapon(0, "Fists", 1, 100, 1)) {}


// getters/setters for base fields are provided by BaseCharacter
const Weapon &Enemy::getCurrentWeapon() const { return currentWeapon; }

void Enemy::setCurrentWeapon(const Weapon &weapon) { this->currentWeapon = weapon; }

void Enemy::attack(MainCharacter &character, std::vector<std::string> *battleLog) {
  uint16_t totalDamage = 0;

  for (int i = 0; i < currentWeapon.getHitReps(); i++) {
    if ((std::rand() % 100) < currentWeapon.getHitChance()) {
      totalDamage += currentWeapon.getDamage();
    }
  }

  character.takeDamage(totalDamage);

  // Log the attack details
  std::ostringstream ss;
  ss << this->getType() << " " << this->getName() << " attacks "
     << character.getName() << " with " << currentWeapon.getName() << " for "
     << totalDamage << " damage!" << " " << character.getName()
     << " current health: " << character.getHealth() << "/" << character.getMaxHealth() << "." << std::endl;

  battleLog->push_back(ss.str());
}

// takeDamage implemented in BaseCharacter
