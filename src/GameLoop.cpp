#include "GameLoop.h"
#include "Enemies/Ghoul.h"
#include "Enemies/Raider.h"
#include "Enemies/SuperMutant.h"
#include "Weapons/BigGun.h"
#include "Weapons/EnergyWeapon.h"
#include "Weapons/MeleeWeapon.h"
#include "Weapons/SmallGun.h"
#include "Weapons/UnarmedWeapon.h"

#include <algorithm>
#include <cstdint>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <vector>

GameLoop::GameLoop()
    : isRunning(true), isMenuRunning(true), isGameRunning(false), menuChoice(0),
      gameChoice(0) {}

static void clearScreen() {
#ifdef _WIN32
  std::system("cls");
#else
  std::system("clear");
#endif
}

void GameLoop::start() {
  srand(static_cast<unsigned int>(time(NULL)));

  // Load data files
  loadWeaponsFile("data/weapons.csv");
  loadEnemiesFile("data/enemies.csv");
  loadCharacterFile("data/character.csv");

  // Assign random weapons to enemies
  if (!allWeapons.empty()) {
    for (auto &enemy : allEnemies) {
      enemy->setCurrentWeapon(allWeapons[rand() % allWeapons.size()]);
    }
  }

  while (isRunning) {
    while (isMenuRunning) {
      clearScreen();

      std::cout << "=== Main Menu ===" << std::endl;
      std::cout << "1. New Game" << std::endl;
      std::cout << "2. Exit" << std::endl;
      std::cout << "Enter your choice: ";
      std::cin >> menuChoice;

      switch (menuChoice) {
      case 1: {
        std::cout << "Starting a new game..." << std::endl;
        clearScreen();

        isGameRunning = true;
        isMenuRunning = false;
        break;
      }
      case 2:
        std::cout << "Exiting game. Goodbye!" << std::endl;
        isMenuRunning = false;
        isRunning = false;
        break;
      default:
        break;
      }
    }

    while (isGameRunning) {
      clearScreen();

      std::cout << "Welcome, " << mainCharacter.getName() << "!" << std::endl;

      if (!currentEnemy) {
        if (!allEnemies.empty())
          currentEnemy = allEnemies[rand() % allEnemies.size()].get();
      }

      if (!currentEnemy) {
        std::cout << "No enemies to encounter." << std::endl;
        isGameRunning = false;
        isRunning = false;
        break;
      }

      std::cout << "You encounter a " << currentEnemy->getType() << " named "
                << currentEnemy->getName() << "!" << std::endl;

      displayCombatantsStats();

      if (!currentBattleLog.empty()) {
        std::cout << "=== Battle Log ===" << std::endl;
        for (const auto &line : currentBattleLog) {
          std::cout << line;
        }
        std::cout << std::endl;
      }

      std::cout << "What is your move?" << std::endl;
      std::cout << "1. Exit Game" << std::endl;
      std::cout << "2. Run Away" << std::endl;

      // Print out the character's weapons as options of attack starting from 2
      for (size_t i = 0; i < mainCharacter.getWeaponList().size(); ++i) {
        std::cout << (i + 3) << ". Attack with "
                  << mainCharacter.getWeaponList()[i].getName() << std::endl;
      }

      std::cout << "Enter your choice: ";
      std::cin >> gameChoice;

      switch (gameChoice) {
      case 1:
        std::cout << "Exiting game. Goodbye!" << std::endl;
        isGameRunning = false;
        isRunning = false;

        break;
      case 2: {
        currentBattleLog.clear();
        std::ostringstream ss;
        ss << "You ran away from the " << currentEnemy->getType() << " named "
           << currentEnemy->getName()
           << "! But you were attacked in the meantime!" << std::endl;
        currentBattleLog.push_back(ss.str());

        currentEnemy->attack(mainCharacter, &currentBattleLog);

        if (mainCharacter.isDead()) {
          mainCharacter.defeatedMessage(*currentEnemy);
          isGameRunning = false;
          isRunning = false;
        }

        if (!allEnemies.empty())
          currentEnemy = allEnemies[rand() % allEnemies.size()].get();
        break;
      }
      default:
        if (gameChoice < 3 ||
            gameChoice >= 3 + mainCharacter.getWeaponList().size()) {
          continue;
        }

        mainCharacter.attack(*currentEnemy,
                             mainCharacter.getWeaponList()[gameChoice - 3],
                             &currentBattleLog);

        if (currentEnemy->getHealth() == 0) {
          currentBattleLog.clear();

          std::ostringstream ss;
          ss << "You have defeated " << currentEnemy->getType() << " named "
             << currentEnemy->getName() << "!" << std::endl;
          currentBattleLog.push_back(ss.str());

          // Remove the defeated enemy from the list
          allEnemies.erase(
              {std::remove_if(allEnemies.begin(), allEnemies.end(),
                              [this](const std::unique_ptr<Enemy> &enemy) {
                                return enemy.get() == currentEnemy;
                              })},
              allEnemies.end());

          if (allEnemies.empty()) {
            std::cout << "Congratulations! You have defeated all enemies!"
                      << std::endl;
            isGameRunning = false;
            isRunning = false;
            break;
          }

          if (allEnemies.empty()) {
            currentEnemy = nullptr;
          } else {
            currentEnemy = allEnemies[rand() % allEnemies.size()].get();
          }
        } else {
          if (currentEnemy)
            currentEnemy->attack(mainCharacter, &currentBattleLog);
        }

        if (mainCharacter.isDead()) {
          mainCharacter.defeatedMessage(*currentEnemy);
          isGameRunning = false;
          isRunning = false;
        }

        break;
      }
    }
  }
}

bool GameLoop::loadEnemiesFile(const std::string &filename) {
  std::ifstream enemyFile(filename);
  if (!enemyFile.is_open()) {
    std::cerr << "Error opening enemy file: " << filename << std::endl;
    return false;
  }

  std::string line;
  while (std::getline(enemyFile, line)) {
    if (line.empty())
      continue;
    if (line.front() == '#')
      continue;

    std::istringstream iss(line);
    std::string token;

    if (!std::getline(iss, token, ','))
      continue;
    std::string enemyType = token;

    if (!std::getline(iss, token, ','))
      continue;
    std::string name = token;

    if (!std::getline(iss, token, ','))
      continue;
    uint16_t maxHealth = static_cast<uint16_t>(std::stoi(token));

    if (!std::getline(iss, token, ','))
      continue;
    uint16_t bottlecaps = static_cast<uint16_t>(std::stoi(token));

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

bool GameLoop::loadWeaponsFile(const std::string &filename) {
  std::ifstream weaponFile(filename);
  if (!weaponFile.is_open()) {
    std::cerr << "Error opening weapon file: " << filename << std::endl;
    return false;
  }

  std::string line;
  while (std::getline(weaponFile, line)) {
    if (line.empty())
      continue;
    if (line.front() == '#')
      continue;

    std::istringstream iss(line);
    std::string token;

    if (!std::getline(iss, token, ','))
      continue;
    std::string weaponType = token;

    if (!std::getline(iss, token, ','))
      continue;
    uint16_t id = static_cast<uint16_t>(std::stoi(token));

    if (!std::getline(iss, token, ','))
      continue;
    std::string name = token;

    if (!std::getline(iss, token, ','))
      continue;
    uint16_t damage = static_cast<uint16_t>(std::stoi(token));

    if (!std::getline(iss, token, ','))
      continue;
    uint8_t hitChance = static_cast<uint8_t>(std::stoi(token));

    if (!std::getline(iss, token, ','))
      continue;
    uint8_t hitReps = static_cast<uint8_t>(std::stoi(token));

    Weapon newWeapon;
    if (weaponType == "BigGun") {
      newWeapon = BigGun(id, name, damage, hitChance, hitReps);
    } else if (weaponType == "SmallGun") {
      newWeapon = SmallGun(id, name, damage, hitChance, hitReps);
    } else if (weaponType == "Unarmed") {
      newWeapon = UnarmedWeapon(id, name, damage, hitChance, hitReps);
    } else if (weaponType == "EnergyWeapon") {
      newWeapon = EnergyWeapon(id, name, damage, hitChance, hitReps);
    } else if (weaponType == "MeleeWeapon") {
      newWeapon = MeleeWeapon(id, name, damage, hitChance, hitReps);
    } else {
      continue;
    }

    allWeapons.emplace_back(newWeapon);
  }

  return true;
}

bool GameLoop::loadCharacterFile(const std::string &filename) {
  std::ifstream characterFile(filename);
  if (!characterFile.is_open()) {
    std::cerr << "Error opening character file: " << filename << std::endl;
    return false;
  }

  // Expected format: Name,MaxHealth,Bottlecaps,WeaponIDs (comma-separated)

  std::string line;
  // Read the first line (skip if it's a comment)
  if (std::getline(characterFile, line)) {
    if (line.front() == '#')
      std::getline(characterFile, line);

    std::istringstream iss(line);
    std::string token;

    // Name
    if (!std::getline(iss, token, ','))
      return false;
    std::string name = token;

    // MaxHealth
    if (!std::getline(iss, token, ','))
      return false;
    uint16_t health = static_cast<uint16_t>(std::stoi(token));

    // Bottlecaps
    if (!std::getline(iss, token, ','))
      return false;
    uint16_t bottlecaps = static_cast<uint16_t>(std::stoi(token));

    mainCharacter = MainCharacter(name, health, bottlecaps);

    // WeaponIDs
    for (int i = 0; std::getline(iss, token, ','); i++) {
      std::cout << "Loading weapon ID: " << token << std::endl;
      uint16_t weaponId = static_cast<uint16_t>(std::stoi(token));
      addMainCharacterWeaponById(weaponId);
    }

    return true;
  }

  return false;
}

void GameLoop::displayCombatantsStats() {
  constexpr int COMBATANT_STATS_WIDTH = 30;
  std::cout << "=== Combatants Stats ===" << std::endl;
  std::cout << std::left << std::setw(COMBATANT_STATS_WIDTH) << "Character"
            << std::left << std::setw(COMBATANT_STATS_WIDTH) << "Enemy"
            << std::endl;

  // Prepare left (character) lines
  std::vector<std::string> leftLines;
  leftLines.push_back(std::string("Name: ") + mainCharacter.getName());
  leftLines.push_back(std::string("Health: ") +
                      std::to_string(mainCharacter.getHealth()) + "/" +
                      std::to_string(mainCharacter.getMaxHealth()));
  leftLines.push_back(std::string("Bottlecaps: ") +
                      std::to_string(mainCharacter.getBottlecaps()));

  const auto &weapons = mainCharacter.getWeaponList();
  // Push an empty-labeled Weapons: line, then list each weapon on its own line
  leftLines.push_back(std::string("Weapons:"));
  if (weapons.empty()) {
    leftLines.push_back(std::string("  None"));
  } else {
    for (const auto &w : weapons) {
      leftLines.push_back(std::string("  ") + w.getName());
    }
  }

  // Prepare right (enemy) lines; enemy has only single weapon so keep entries
  std::vector<std::string> rightLines;
  rightLines.push_back(std::string("Name: ") + currentEnemy->getName());
  rightLines.push_back(std::string("Health: ") +
                       std::to_string(currentEnemy->getHealth()) + "/" +
                       std::to_string(currentEnemy->getMaxHealth()));
  rightLines.push_back(std::string("Bottlecaps: ") +
                       std::to_string(currentEnemy->getBottlecaps()));
  // Weapon label line (empty), then the enemy's weapon on the next line
  rightLines.push_back(std::string("Weapon:"));
  rightLines.push_back(std::string("  ") +
                       currentEnemy->getCurrentWeapon().getName());

  // Print rows: loop up to the max of left/right lines
  size_t rows = std::max(leftLines.size(), rightLines.size());
  for (size_t i = 0; i < rows; ++i) {
    const std::string &l =
        (i < leftLines.size() ? leftLines[i] : std::string());
    const std::string &r =
        (i < rightLines.size() ? rightLines[i] : std::string());

    std::cout << std::left << std::setw(COMBATANT_STATS_WIDTH) << l << std::left
              << std::setw(COMBATANT_STATS_WIDTH) << r << std::endl;
  }

  std::cout << "\n\n";
}

void GameLoop::addMainCharacterWeaponById(uint16_t weaponId) {
  for (const Weapon &weapon : allWeapons) {
    if (weapon.getId() == weaponId) {

      std::cout << "Adding weapon: " << weapon.getName()
                << " to main character." << std::endl;
      mainCharacter.addWeapon(weapon);
      break;
    }
  }
}
