#include "Enemies/Enemy.h"
#include "MainCharacter.h"
#include "Weapons/UnarmedWeapon.h"
#include <iostream>
#include <sstream>
#include <vector>

//////////////////
// Constructors //
//////////////////

Enemy::Enemy(std::string name, uint16_t maxHealth, uint16_t bottlecaps)
    : BaseCharacter(std::move(name), maxHealth, bottlecaps) {}

///////////////
/// Getters ///
///////////////

const Weapon &Enemy::getCurrentWeapon() const { return *currentWeapon; }

///////////////
/// Setters ///
/// ///////////

void Enemy::setCurrentWeapon(const Weapon &weapon) { currentWeapon = &weapon; }

///////////////
/// Methods ///
///////////////

void Enemy::attack(MainCharacter &character,
                   std::vector<std::string> *battleLog) {
  uint16_t totalDamage = 0;

  for (int i = 0; i < currentWeapon->getHitReps(); i++) {
    if ((std::rand() % 100) < currentWeapon->getHitChance()) {
      totalDamage += currentWeapon->getDamage();
    }
  }

  character.takeDamage(totalDamage);

  // Log the attack details
  std::ostringstream ss;
  ss << this->getType() << " " << this->getName() << " attacks "
     << character.getName() << " with " << currentWeapon->getType() << " " << currentWeapon->getName() << " for "
     << totalDamage << " damage!" << " " << character.getName()
     << " current health: " << character.getHealth() << "/"
     << character.getMaxHealth() << "." << std::endl;

  battleLog->push_back(ss.str());
}

std::string Enemy::getType() const { return "Enemy"; }
