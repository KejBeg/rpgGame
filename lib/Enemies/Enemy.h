#ifndef ENEMY_H
#define ENEMY_H

#include <string>
#include "Weapons/Weapon.h"


class Character;


class Enemy {
private:
  std::string name;
  int health;
  int bottlecaps;

  Weapon currentWeapon;
public:
  // Construct an Enemy with explicit initial state
  Enemy(std::string name, int health, int bottlecaps, const Weapon &weapon);

  virtual ~Enemy() = default;

  /**
   * @brief Get the enemy's name.
 * @return const std::string& Reference to the stored name.
   */
  const std::string& getName() const;

  /**
   * @brief Get the enemy's current health.
   * @return int Health value.
   */
  int getHealth() const;

  /**
   * @brief Get the enemy's bottlecap count.
   * @return int Number of bottlecaps.
   */
  int getBottlecaps() const;

  /**
   * @brief Access the enemy's currently equipped weapon (read-only).
   * @return const Weapon& Reference to the current weapon.
   */
  const Weapon& getCurrentWeapon() const;

  /**
   * @brief Access the enemy's currently equipped weapon for modification.
   * @return Weapon& Reference to the current weapon.
   */
  Weapon& getCurrentWeapon();

  /**
   * @brief Set the enemy's name.
   * @param name New name to assign.
   */
  void setName(const std::string& name);

  /**
   * @brief Set the enemy's health.
   * @param health New health value.
   */
  void setHealth(int health);

  /**
   * @brief Set the enemy's bottlecap count.
   * @param bottlecaps New bottlecap value (non-negative).
   */
  void setBottlecaps(int bottlecaps);

  /**
   * @brief Set the enemy's currently equipped weapon.
   * @param weapon Weapon to assign as the current weapon.
   */
  void setCurrentWeapon(const Weapon& weapon);

    /**
    * @brief Apply damage to the enemy, reducing health accordingly.
    * @param damage Amount of damage to apply (non-negative).
    */
  void takeDamage(uint16_t damage);

  /**
   * @brief Perform an attack against a character.
   * @param character The character to attack (may be modified).
   */
  void attack(Character &character);

  /**
   * @brief Get the type of the enemy (e.g., "Ghoul", "SuperMutant", "Raider").
 * @return std::string Type of the enemy.
   *
   * Make this pure virtual so every concrete enemy must provide a type.
   */
  virtual std::string getType() const = 0;

};

#endif // !ENEMY_H
