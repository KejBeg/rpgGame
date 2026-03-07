#ifndef GAME_LOOP_H
#define GAME_LOOP_H

#include "Enemies/Enemy.h"
#include "MainCharacter.h"
#include "Weapons/Weapon.h"
#include <memory>
#include <string>
#include <vector>

/**
 * @brief The GameLoop class manages the main game loop, including the menu and
 * combat phases.
 *
 * The GameLoop class is responsible for initializing the game state, handling
 * user input, managing the flow of the game, and coordinating interactions
 * between the main character and enemies. It loads game data from files,
 * updates combat logs, and displays relevant information to the player.
 */
class GameLoop {
private:
  bool isRunning;
  bool isMenuRunning;
  bool isGameRunning;
  int menuChoice;
  int gameChoice;

  std::vector<std::string> currentBattleLog;

  std::vector<std::unique_ptr<Enemy>> allEnemies;
  std::vector<Weapon> allWeapons;
  MainCharacter mainCharacter;

  Enemy *currentEnemy = nullptr;

public:
  ////////////////////
  /// Constructors ///
  ////////////////////
  ///
  /**
   * @brief Construct a new GameLoop object and initialize the game state.
   */
  GameLoop();

  ///////////////
  /// Methods ///
  ///////////////

  /**
   * @brief Start the main game loop, including the menu and combat phases.
   *
   * This method manages the overall flow of the game, allowing the player to
   * navigate through the menu, engage in combat with enemies, and view combat
   * logs. It continues running until the player chooses to exit or is defeated.
   */
  void start();

  /**
   * @brief Adds a weapon to the main character's inventory based on the
   * provided weapon ID.
   * @param weaponId The unique identifier of the weapon to be added to the main
   * character's inventory.
   */
  void addMainCharacterWeaponById(uint16_t weaponId);

  /**
   * @brief Displays the current stats of both the main character and the
   * current enemy.
   *
   * This method provides a clear overview of the health, bottlecaps, and
   * equipped weapons for both combatants, allowing the player to make informed
   * decisions during combat.
   */
  void displayCombatantsStats();

  /**
   * @brief Loads enemy data from a specified file and populates the allEnemies
   * vector.
   * @param filename The name of the file containing enemy data.
   * @return true if the file was successfully loaded and parsed; false
   * otherwise. The file should be formatted with each line representing an
   * enemy, containing Type, Name, MaxHealth, Bottlecaps.
   */
  bool loadEnemiesFile(const std::string &filename);

  /**
   * @brief Loads weapon data from a specified file and populates the allWeapons
   * vector.
   * @param filename The name of the file containing weapon data.
   * @return true if the file was successfully loaded and parsed; false
   * otherwise. The file should be formatted with each line representing a
   * weapon, containing Type, ID, Name, Damage, HitChance, HitReps.
   */
  bool loadWeaponsFile(const std::string &filename);

  /**
   * @brief Loads main character data from a specified file and initializes the
   * mainCharacter object.
   * @param filename The name of the file containing main character data.
   * @return true if the file was successfully loaded and parsed; false
   * otherwise. The file should be formatted with a single line containing Name,
   * MaxHealth, Bottlecaps, WeaponIDs (comma-separated list of weapon IDs).
   */
  bool loadCharacterFile(const std::string &filename);
};

#endif
