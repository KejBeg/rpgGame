#ifndef ENEMY_H
#define ENEMY_H

#include "BaseCharacter.h"
#include "Weapons/Weapon.h"
#include <cstdint>
#include <string>
#include <vector>

class MainCharacter;

class Enemy : public BaseCharacter {
private:
  const Weapon *currentWeapon = nullptr;

public:
  ////////////////////
  /// Constructors ///
  ////////////////////

  /**
   * @brief Construct a new Enemy object with specified attributes.
   * @param name Name of the enemy.
   * @param maxHealth Maximum health value for the enemy.
   * @param bottlecaps Initial bottlecap count for the enemy.
   * The current weapon is initialized to a default "Fists" weapon with 1
   * damage.
   */
  Enemy(std::string name, uint16_t maxHealth, uint16_t bottlecaps);
  

  ///////////////
  /// Getters ///
  ///////////////

  /**
   * @brief Access the enemy's currently equipped weapon (read-only).
   * @return const Weapon& Reference to the current weapon.
   */
  const Weapon &getCurrentWeapon() const;

  ///////////////
  /// Setters ///
  ///////////////

  /**
   * @brief Set the enemy's currently equipped weapon.
   * @param weapon Weapon to assign as the current weapon.
   */
  void setCurrentWeapon(const Weapon &weapon);

  ///////////////
  /// Methods ///
  ///////////////

  /**
   * @brief Perform an attack against a character.
   * @param character The character to attack
   */
  void attack(MainCharacter &character,
              std::vector<std::string> *battleLog = nullptr);

  /**
   * @brief Get the type of the enemy (e.g., "Ghoul", "SuperMutant", "Raider").
   * @return std::string Type of the enemy.
   */
  virtual std::string getType() const;
};

#endif // !ENEMY_H
