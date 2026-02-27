#include "Character.h"
#include "Enemies/Ghoul.h"
#include "Enemies/Raider.h"
#include "Enemies/SuperMutant.h"
#include "Weapons/BigGun.h"
#include "Weapons/EnergyWeapon.h"
#include "Weapons/MeleeWeapon.h"
#include "Weapons/SmallGun.h"
#include "Weapons/UnarmedWeapon.h"
#include <cstdlib>
#include <iostream>
#include <vector>
#include <memory>

// Clear regardless of system
#ifdef _WIN32
#define CLEAR_COMMAND "cls"
#else
#define CLEAR_COMMAND "clear"
#endif

void createWeapons(std::vector<Weapon> &allWeapons) {
  allWeapons.push_back(SmallGun("9mm Pistol", 10, 30, 1));
  allWeapons.push_back(BigGun("Assault Rifle", 30, 50, 3));
  allWeapons.push_back(EnergyWeapon("Laser Rifle", 50, 40, 2));
}

void createEnemies(std::vector<std::unique_ptr<Enemy>> &allEnemies) {
  allEnemies.push_back(std::make_unique<Raider>("Fiend", 100, 20));
  allEnemies.push_back(std::make_unique<Ghoul>("Ghoul", 80, 15));
  allEnemies.push_back(std::make_unique<SuperMutant>("Super Mutant", 150, 30));

}

int main() {
  bool isRunning = true;
  bool isMenuRunning = true;
  bool isGameRunning = false;

  int menuChoice;
  srand(time(NULL));

  // Weapons
  std::vector<Weapon> allWeapons;
  createWeapons(allWeapons);

  // Enemies
  std::vector<std::unique_ptr<Enemy>> allEnemies;
  createEnemies(allEnemies);

  // Main character
  Character mainCharacter =
      Character("Courier 6", 100, 0, {allWeapons[rand() % allWeapons.size()]});

  while (isRunning) {
    while (isMenuRunning) {
      system(CLEAR_COMMAND);
      
      std::cout << "=== Main Menu ===" << std::endl;
      std::cout << "1. New Game" << std::endl;
      std::cout << "2. Load Game" << std::endl;
      std::cout << "3. Exit" << std::endl;
      std::cout << "Enter your choice: ";
      std::cin >> menuChoice;

      switch (menuChoice) {
      case 1:
        std::cout << "Starting a new game..." << std::endl;
        isGameRunning = true;
        isMenuRunning = false;
        break;
      case 2:
        std::cout << "Loading game..." << std::endl;
        break;
      case 3:
        std::cout << "Exiting game. Goodbye!" << std::endl;
        isRunning = false;
        break;
      default:
        std::cout << "Invalid choice. Please try again." << std::endl;
        break;
      }
    }

    while (isGameRunning) {
      system(CLEAR_COMMAND);
    }
  }

  return 0;
}
