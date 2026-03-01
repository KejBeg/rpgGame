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
#include <iomanip>
#include <iostream>
#include <memory>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <cctype>

// Clear regardless of system
#ifdef _WIN32
#define CLEAR_COMMAND "cls"
#else
#define CLEAR_COMMAND "clear"
#endif

#define COMBATANT_STATS_WIDTH 30

/**
 * @brief Create a variety of enemies and add them to the provided vector.
 * Each enemy is created with a unique name, health, and bottlecap count.
 * @param allEnemies Reference to a vector that will store unique pointers to
 * the created enemies.
 */
void createEnemies(std::vector<std::unique_ptr<Enemy>> &allEnemies) {
  allEnemies.push_back(std::make_unique<Raider>("Fiend", 100, 20));
  allEnemies.push_back(std::make_unique<Ghoul>("Ghoul", 80, 15));
  allEnemies.push_back(std::make_unique<SuperMutant>("Super Mutant", 150, 30));
}


/**
 * @brief Display the stats of both the character and the enemy in a formatted
 * manner.
 * @param character The main character whose stats are to be displayed.
 * @param enemy The enemy whose stats are to be displayed.
 */
void DisplayCombatantsStats(const Character &character, const Enemy &enemy) {
  std::cout << "=== Combatants Stats ===" << std::endl;
  // Header
  std::cout << std::left << std::setw(COMBATANT_STATS_WIDTH) << "Character"
            << std::left << std::setw(COMBATANT_STATS_WIDTH) << "Enemy"
            << std::endl;

  // Name
  std::cout << std::left << std::setw(COMBATANT_STATS_WIDTH)
            << ("Name: " + character.getName()) << std::left
            << std::setw(COMBATANT_STATS_WIDTH) << ("Name: " + enemy.getName())
            << std::endl;

  // Health
  std::cout << std::left << std::setw(COMBATANT_STATS_WIDTH)
            << ("Health: " + std::to_string(character.getHealth()) + "/" +
                std::to_string(character.getMaxHealth()))
            << std::left << std::setw(COMBATANT_STATS_WIDTH)
            << ("Health: " + std::to_string(enemy.getHealth()) + "/" +
                std::to_string(enemy.getMaxHealth()))
            << std::endl;

  // Bottlecaps
  std::cout << std::left << std::setw(COMBATANT_STATS_WIDTH)
            << ("Bottlecaps: " + std::to_string(character.getBottlecaps()))
            << std::left << std::setw(COMBATANT_STATS_WIDTH)
            << ("Bottlecaps: " + std::to_string(enemy.getBottlecaps()))
            << std::endl;

  // Weapons
  std::cout << std::left << std::setw(COMBATANT_STATS_WIDTH)
            << "Weapons: " +
                   [&character]() {
                     std::string weapons;
                     for (const auto &weapon : character.getWeaponList()) {
                       weapons += weapon.getName() + " ";
                     }
                     return weapons;
                   }()
            << std::left << std::setw(COMBATANT_STATS_WIDTH)
            << ("Weapon: " + enemy.getCurrentWeapon().getName()) << std::endl;
  std::cout << "\n\n";
}

bool loadWeaponFile(const std::string &filename, std::vector<Weapon> &allWeapons) {
  std::ifstream weaponFile(filename);
  if (!weaponFile.is_open()) {
    std::cerr << "Error opening weapon file: " << filename << std::endl;
    return false;
  }

  // for each line in the file, parse the weapon data and create a Weapon object
  std::string line;
  while (std::getline(weaponFile, line)) {
    if (line.empty()) continue;           
    if (line.front() == '#') continue;

    std::istringstream iss(line);
    std::string token;

    if (!std::getline(iss, token, ',')) continue;
    uint16_t id = static_cast<uint16_t>(std::stoi(token));

    if (!std::getline(iss, token, ',')) continue;
    std::string name = token;

    if (!std::getline(iss, token, ',')) continue;
    uint16_t damage = static_cast<uint16_t>(std::stoi(token));

    if (!std::getline(iss, token, ',')) continue;
    uint8_t hitChance = static_cast<uint8_t>(std::stoi(token));

    if (!std::getline(iss, token, ',')) continue;
    uint8_t hitReps = static_cast<uint8_t>(std::stoi(token));

    // Construct and store the weapon 
    allWeapons.emplace_back(id, name, damage, hitChance, hitReps);
  }

  return true;
}


int main() {
  bool isRunning = true;
  bool isMenuRunning = true;
  bool isGameRunning = false;

  int menuChoice;
  int gameChoice;
  srand(time(NULL));

  // Weapons
  std::vector<Weapon> allWeapons;
  loadWeaponFile("weapons.csv", allWeapons);

  // Enemies
  std::vector<std::unique_ptr<Enemy>> allEnemies;
  createEnemies(allEnemies);

  // Main character
  Character mainCharacter =
      Character("Unknown", 100, 0, {allWeapons[rand() % allWeapons.size()]});

  while (isRunning) {
    while (isMenuRunning) {
      system(CLEAR_COMMAND);

      // Main menu options
      std::cout << "=== Main Menu ===" << std::endl;
      std::cout << "1. New Game" << std::endl;
      std::cout << "2. Load Game" << std::endl;
      std::cout << "3. Exit" << std::endl;
      std::cout << "Enter your choice: ";
      std::cin >> menuChoice;

      // Handle menu choice
      switch (menuChoice) {
      case 1:
        std::cout << "Starting a new game..." << std::endl;

        // Main Character name
        {
          system(CLEAR_COMMAND);
          std::string playerName;
          std::cout << "Enter your character's name: ";
          std::cin >> playerName;
          mainCharacter.setName(playerName);
        }

        // Transition to game loop
        isGameRunning = true;
        isMenuRunning = false;
        break;
      case 2:
        // TODO: Implement load game functionality
        std::cout << "Loading game..." << std::endl;
        break;
      case 3:
        // Exit the game
        std::cout << "Exiting game. Goodbye!" << std::endl;
        isMenuRunning = false;
        isRunning = false;
        break;
      default:
        std::cout << "Invalid choice. Please try again." << std::endl;
        break;
      }
    }

    while (isGameRunning) {
      system(CLEAR_COMMAND);

      std::cout << "Welcome, " << mainCharacter.getName() << "!" << std::endl;

      // Randomly select an enemy to encounter
      Enemy &currentEnemy = *allEnemies[rand() % allEnemies.size()];
      std::cout << "You encounter a " << currentEnemy.getType() << " named "
                << currentEnemy.getName() << "!" << std::endl;

      DisplayCombatantsStats(mainCharacter, currentEnemy);

      std::cout << "What is your move?" << std::endl;
      std::cout << "1. Attack" << std::endl;
      std::cout << "2. Run Away" << std::endl;
      std::cout << "Enter your choice: ";
      std::cin >> gameChoice;

      switch (gameChoice) {
      case 1:
          mainCharacter.attack(currentEnemy, mainCharacter.getWeaponList().front());
          if (currentEnemy.getHealth() == 0) {
              std::cout << "You defeated the " << currentEnemy.getType() << " "
                        << currentEnemy.getName() << "!" << std::endl;
  
          }
        break;
      case 2:
        break;
      default:
        std::cout << "Invalid choice. Please try again." << std::endl;
        break;
      }

      std::cin >> gameChoice;
    }
  }

  return 0;
}
