#include "MainCharacter.h"
#include "Enemies/Enemy.h"
#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <vector>

MainCharacter::MainCharacter(std::string name, uint16_t maxHealth,
                             uint16_t bottlecaps, std::list<Weapon> weaponList)
    : BaseCharacter(std::move(name), maxHealth, bottlecaps),
      weaponList(std::move(weaponList)) {}

const std::list<Weapon> &MainCharacter::getWeaponList() const {
  return weaponList;
}
std::list<Weapon> &MainCharacter::getWeaponList() { return weaponList; }

void MainCharacter::setWeaponList(const std::list<Weapon> &weaponList) {
  this->weaponList = weaponList;
}

bool MainCharacter::isDead() { return this->getHealth() == 0; }

void MainCharacter::defeated(Enemy &enemy) {
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
     << enemy.getName() << " with " << weapon.getName() << " for "
     << totalDamage << " damage!" << " " << enemy.getName()
     << " current health: " << enemy.getHealth() << "/" << enemy.getMaxHealth()
     << "." << std::endl;

  if (battleLog)
    battleLog->push_back(ss.str());
}
