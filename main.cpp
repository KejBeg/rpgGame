#include "Enemies/Ghoul.h"
#include "Enemies/Raider.h"
#include "Enemies/SuperMutant.h"
#include "MainCharacter.h"
#include "Weapons/BigGun.h"
#include "Weapons/EnergyWeapon.h"
#include "Weapons/MeleeWeapon.h"
#include "Weapons/SmallGun.h"
#include "Weapons/UnarmedWeapon.h"
#include <algorithm>
#include <cctype>
#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <memory>
#include <sstream>
#include <vector>

// Clear regardless of system
#ifdef _WIN32
#define CLEAR_COMMAND "cls"
#else
#define CLEAR_COMMAND "clear"
#endif

#define COMBATANT_STATS_WIDTH 30

/**
 * @brief Display the stats of both the character and the enemy in a formatted
 * manner.
 * @param character The main character whose stats are to be displayed.
 * @param enemy The enemy whose stats are to be displayed.
 */
void DisplayCombatantsStats(const MainCharacter &character,
                            const Enemy &enemy) {
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

/**
 * @brief Loads enemy data from a specified file and populates a vector with
 * Enemy objects.
 * @param filename The path to the enemy data file (CSV format).
 * @param allEnemies A reference to a vector that will be populated with unique
 * pointers to Enemy objects.
 * @return true if the file was successfully loaded and parsed; false otherwise.
 * The expected format of each line in the file is:
 * EnemyType, Name, MaxHealth, Bottlecaps
 * Lines starting with '#' or empty lines are ignored as comments or whitespace.
 */
bool loadEnemyFile(const std::string &filename,
                   std::vector<std::unique_ptr<Enemy>> &allEnemies) {
  std::ifstream enemyFile(filename);
  if (!enemyFile.is_open()) {
    std::cerr << "Error opening enemy file: " << filename << std::endl;
    return false;
  }

  // for each line in the file, parse the enemy data and create an Enemy object
  std::string line;
  while (std::getline(enemyFile, line)) {
    if (line.empty())
      continue;
    if (line.front() == '#')
      continue;

    std::istringstream iss(line);
    std::string token;

    // Expected format: EnemyType, Name, MaxHealth, Bottlecaps

    // Enemy Type
    if (!std::getline(iss, token, ','))
      continue;
    std::string enemyType = token;

    // Name
    if (!std::getline(iss, token, ','))
      continue;
    std::string name = token;

    // Max Health
    if (!std::getline(iss, token, ','))
      continue;
    uint16_t maxHealth = static_cast<uint16_t>(std::stoi(token));

    // Bottlecaps
    if (!std::getline(iss, token, ','))
      continue;
    uint16_t bottlecaps = static_cast<uint16_t>(std::stoi(token));

    // Construct and store the enemy
    if (enemyType.empty())
      continue;
    else if (enemyType == "Ghoul") {
      allEnemies.push_back(
          std::make_unique<Ghoul>(name, maxHealth, bottlecaps));
    } else if (enemyType == "Raider") {
      allEnemies.push_back(
          std::make_unique<Raider>(name, maxHealth, bottlecaps));
    } else if (enemyType == "SuperMutant") {
      allEnemies.push_back(
          std::make_unique<SuperMutant>(name, maxHealth, bottlecaps));
    } else {
      continue;
    }
  }

  return true;
}

bool loadWeaponFile(const std::string &filename,
                    std::vector<Weapon> &allWeapons) {
  std::ifstream weaponFile(filename);
  if (!weaponFile.is_open()) {
    std::cerr << "Error opening weapon file: " << filename << std::endl;
    return false;
  }

  // for each line in the file, parse the weapon data and create a Weapon object
  std::string line;
  while (std::getline(weaponFile, line)) {
    if (line.empty())
      continue;
    if (line.front() == '#')
      continue;

    std::istringstream iss(line);
    std::string token;

    // Expected format: WeaponType, ID,Name,Damage,HitChance,HitReps

    // Weapon Type
    if (!std::getline(iss, token, ','))
      continue;
    std::string weaponType = token;

    // ID
    if (!std::getline(iss, token, ','))
      continue;
    uint16_t id = static_cast<uint16_t>(std::stoi(token));

    // Name
    if (!std::getline(iss, token, ','))
      continue;
    std::string name = token;

    // Damage
    if (!std::getline(iss, token, ','))
      continue;
    uint16_t damage = static_cast<uint16_t>(std::stoi(token));

    // Hit Chance
    if (!std::getline(iss, token, ','))
      continue;
    uint8_t hitChance = static_cast<uint8_t>(std::stoi(token));

    // Hit Reps
    if (!std::getline(iss, token, ','))
      continue;
    uint8_t hitReps = static_cast<uint8_t>(std::stoi(token));

    // Construct and store the weapon
    Weapon newWeapon;
    if (weaponType.empty())
      continue;
    else if (weaponType == "SmallGun") {
      newWeapon = SmallGun(id, name, damage, hitChance, hitReps);
    } else if (weaponType == "BigGun") {
      newWeapon = BigGun(id, name, damage, hitChance, hitReps);
    } else if (weaponType == "EnergyWeapon") {
      newWeapon = EnergyWeapon(id, name, damage, hitChance, hitReps);
    } else if (weaponType == "MeleeWeapon") {
      newWeapon = MeleeWeapon(id, name, damage, hitChance, hitReps);
    } else if (weaponType == "UnarmedWeapon") {
      newWeapon = UnarmedWeapon(id, name, damage, hitChance, hitReps);
    } else {
      continue;
    }

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
  loadWeaponFile("data/weapons.csv", allWeapons);

  // Enemies
  std::vector<std::unique_ptr<Enemy>> allEnemies;
  loadEnemyFile("data/enemies.csv", allEnemies);

  // For each enemy, get a random weapon
  for (auto &enemy : allEnemies) {
    enemy->setCurrentWeapon(allWeapons[rand() % allWeapons.size()]);
  }

  // Main character
  MainCharacter mainCharacter = MainCharacter(
      "Unknown", 100, 0, {allWeapons[rand() % allWeapons.size()]});

  // Battle log for the current fight (stores human-readable lines)
  std::vector<std::string> currentBattleLog;

  while (isRunning) {
    while (isMenuRunning) {
      system(CLEAR_COMMAND);

      // Main menu options
      std::cout << "=== Main Menu ===" << std::endl;
      std::cout << "1. New Game" << std::endl;
      std::cout << "2. Exit" << std::endl;
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
        // Exit the game
        std::cout << "Exiting game. Goodbye!" << std::endl;
        isMenuRunning = false;
        isRunning = false;
        break;
      default:
        break;
      }
    }

    // pointer to the current enemy; we reselect when it's nullptr or after
    // removal
    Enemy *currentEnemy = nullptr;

    while (isGameRunning) {
      system(CLEAR_COMMAND);

      std::cout << "Welcome, " << mainCharacter.getName() << "!" << std::endl;

      // Randomly select an enemy to encounter
      // ensure we have a valid enemy selected for this encounter
      if (!currentEnemy) {
        currentEnemy = allEnemies[rand() % allEnemies.size()].get();
      }

      std::cout << "You encounter a " << currentEnemy->getType() << " named "
                << currentEnemy->getName() << "!" << std::endl;

      DisplayCombatantsStats(mainCharacter, *currentEnemy);

      // Print the current battle log each loop so the player can see history
      if (!currentBattleLog.empty()) {
        std::cout << "=== Battle Log ===" << std::endl;
        for (const auto &line : currentBattleLog) {
          std::cout << line;
        }
        std::cout << std::endl;
      }

      std::cout << "What is your move?" << std::endl;
      std::cout << "1. Attack" << std::endl;
      std::cout << "2. Run Away" << std::endl;
      std::cout << "Enter your choice: ";
      std::cin >> gameChoice;

      switch (gameChoice) {
      case 1:
        mainCharacter.attack(*currentEnemy,
                             mainCharacter.getWeaponList().front(),
                             &currentBattleLog);
        if (currentEnemy->getHealth() == 0) {
          std::cout << "You defeated the " << currentEnemy->getType() << " "
                    << currentEnemy->getName() << "!" << std::endl;

          // Remove enemy from circulation
          allEnemies.erase(
              std::remove_if(
                  allEnemies.begin(), allEnemies.end(),
                  [currentEnemy](const std::unique_ptr<Enemy> &enemy) {
                    return enemy.get() == currentEnemy;
                  }),
              allEnemies.end());

          // Choose a new enemy
          if (allEnemies.empty()) {
            std::cout << "Congratulations! You have defeated all enemies!"
                      << std::endl;

            isGameRunning = false;
            isRunning = false;
            break;
          }

          currentBattleLog.clear();

          // pick a new enemy (reset pointer first to avoid using dangling ptr)
          if (allEnemies.empty()) {
            currentEnemy = nullptr;
          } else {
            currentEnemy = allEnemies[rand() % allEnemies.size()].get();
          }
        }

        if (currentEnemy)
          currentEnemy->attack(mainCharacter, &currentBattleLog);

        // If the main character is defeated, end the game
        if (mainCharacter.isDead()) {
          mainCharacter.defeated(*currentEnemy);
          isGameRunning = false;
          isRunning = false;
        }

        break;
      case 2: {
        currentBattleLog.clear();
        std::ostringstream ss;
        ss << "You ran away from the " << currentEnemy->getType() << " named "
           << currentEnemy->getName()
           << "! But you were attacked in the meantime!" << std::endl;
        currentBattleLog.push_back(ss.str());

        currentEnemy->attack(mainCharacter, &currentBattleLog);

        // If the main character is defeated, end the game
        if (mainCharacter.isDead()) {
          mainCharacter.defeated(*currentEnemy);
          isGameRunning = false;
          isRunning = false;
        }

        // Select a new enemy to encounter
        currentEnemy = allEnemies[rand() % allEnemies.size()].get();
        break;
      }
      default:
        break;
      }
    }
  }

  return 0;
}
