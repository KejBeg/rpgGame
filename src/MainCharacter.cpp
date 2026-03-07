#include "MainCharacter.h"
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <vector>

////////////////////
/// Constructors ///
////////////////////
MainCharacter::MainCharacter() : BaseCharacter("", 100, 0) {}

MainCharacter::MainCharacter(std::string name, uint16_t maxHealth,
                             uint16_t bottlecaps)
    : BaseCharacter(std::move(name), maxHealth, bottlecaps) {}

////////////////
//// Getters ///
////////////////
const std::vector<Weapon> &MainCharacter::getWeaponList() const {
  return weaponList;
}
std::vector<Weapon> &MainCharacter::getWeaponList() { return weaponList; }

///////////////
/// Setters ///
///////////////
void MainCharacter::setWeaponList(const std::vector<Weapon> &weaponList) {
  this->weaponList = weaponList;
}

///////////////
/// Methods ///
///////////////
bool MainCharacter::isDead() { return this->getHealth() == 0; }

void MainCharacter::defeatedMessage(Enemy &enemy) {
  std::cout << "You have been defeated by the " << enemy.getType() << " "
            << enemy.getName() << "!" << std::endl;
  std::cout << "Game Over!" << std::endl;
}

void MainCharacter::attack(Enemy &enemy, const Weapon &weapon,
                           std::vector<std::string> *battleLog) {
  uint16_t totalDamage = 0;

  for (int i = 0; i < weapon.getHitReps(); i++) {
    if ((std::rand() % 100) < weapon.getHitChance()) {
      totalDamage += weapon.getDamage();
    }
  }

  enemy.takeDamage(totalDamage);

  std::ostringstream ss;
  ss << this->getName() << " attacks " << enemy.getType() << " "
     << enemy.getName() << " with " << weapon.getType() << " " << weapon.getName() << " for "
     << totalDamage << " damage!" << " " << enemy.getName()
     << " current health: " << enemy.getHealth() << "/" << enemy.getMaxHealth()
     << "." << std::endl;

  if (battleLog)
    battleLog->push_back(ss.str());
}

void MainCharacter::addWeapon(const Weapon &weapon) {
  weaponList.push_back(weapon);
}
