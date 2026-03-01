#ifndef ENEMY_H
#define ENEMY_H

#include "Weapons/Weapon.h"
#include <cstdint>
#include <string>
#include <vector>

class Character;

class Enemy {
private:
  std::string name;

  uint16_t health;
  uint16_t maxHealth;
  uint16_t bottlecaps;

  Weapon currentWeapon;

public:
  /**
   * @brief Construct a new Enemy object with specified attributes.
   * @param name Name of the enemy.
   * @param maxHealth Maximum health value for the enemy.
   * @param bottlecaps Initial bottlecap count for the enemy.
   * The current weapon is initialized to a default "Fists" weapon with 1 damage.
   */
  Enemy(std::string name, uint16_t maxHealth, uint16_t bottlecaps);

  virtual ~Enemy() = default;

  /**
   * @brief Get the enemy's name.
   * @return const std::string& Reference to the stored name.
   */
  const std::string &getName() const;

  /**
   * @brief Get the enemy's current health.
   * @return uint16_t Health value.
   */
  uint16_t getHealth() const;

  /**
   * @brief Get the enemy's bottlecap count.
   * @return uint16_t Number of bottlecaps.
   */
  uint16_t getBottlecaps() const;

  /**
   * @brief Get the enemy's maximum health.
   * @return uint16_t Maximum health value.
   */
  uint16_t getMaxHealth() const;

  /**
   * @brief Set the enemy's maximum health.
   * @param maxHealth New maximum health value.
   */
  void setMaxHealth(uint16_t maxHealth);

  /**
   * @brief Access the enemy's currently equipped weapon (read-only).
   * @return const Weapon& Reference to the current weapon.
   */
  const Weapon &getCurrentWeapon() const;

  /**
   * @brief Access the enemy's currently equipped weapon for modification.
   * @return Weapon& Reference to the current weapon.
   */
  Weapon &getCurrentWeapon();

  /**
   * @brief Set the enemy's name.
   * @param name New name to assign.
   */
  void setName(const std::string &name);

  /**
   * @brief Set the enemy's health.
   * @param health New health value.
   */
  void setHealth(uint16_t health);

  /**
   * @brief Set the enemy's bottlecap count.
   * @param bottlecaps New bottlecap value (non-negative).
   */
  void setBottlecaps(uint16_t bottlecaps);

  /**
   * @brief Set the enemy's currently equipped weapon.
   * @param weapon Weapon to assign as the current weapon.
   */
  void setCurrentWeapon(const Weapon &weapon);

  /**
   * @brief Apply damage to the enemy, reducing health accordingly.
   * @param damage Amount of damage to apply (non-negative).
   */
  void takeDamage(uint16_t damage);

  /**
   * @brief Perform an attack against a character.
   * @param character The character to attack (may be modified).
   */
  void attack(Character &character, std::vector<std::string> *battleLog = nullptr);

  /**
   * @brief Get the type of the enemy (e.g., "Ghoul", "SuperMutant", "Raider").
   * @return std::string Type of the enemy.
   *
   * Make this pure virtual so every concrete enemy must provide a type.
   */
  virtual std::string getType() const = 0;
};

#endif // !ENEMY_H
