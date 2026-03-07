#ifndef MAIN_CHARACTER_H
#define MAIN_CHARACTER_H

#include "BaseCharacter.h"
#include "Weapons/Weapon.h"
#include <cstdint>
#include <string>
#include <vector>
#include "Enemies/Enemy.h"


/**
 * @brief Represents the main character controlled by the player.
 *
 * The MainCharacter class extends BaseCharacter and includes a list of
 * weapons that the character can use in combat. It provides methods for
 * attacking enemies, managing the weapon inventory, and handling defeat.
 */
class MainCharacter : public BaseCharacter {
private:
  std::vector<Weapon> weaponList;

public:
  ////////////////////
  /// Constructors ///
  ////////////////////

  /**
   * @brief Construct a new MainCharacter object with default attributes.
   *
   * The default constructor initializes the main character with a default name,
   * maximum health, and bottlecap count. The weapon list is initialized as
   * empty.
   */
  MainCharacter();

  /**
   * @brief Construct a new MainCharacter object.
   * @param name Name of the main character.
   * @param maxHealth Maximum health value for the main character.
   * @param bottlecaps Initial bottlecap count for the main character.
   * The weapon list is initialized as empty.
   */
  MainCharacter(std::string name, uint16_t maxHealth, uint16_t bottlecaps);

  ///////////////
  /// Getters ///
  ///////////////
  const std::vector<Weapon> &getWeaponList() const;
  std::vector<Weapon> &getWeaponList();

  ///////////////
  /// Setters ///
  ///////////////
  void setWeaponList(const std::vector<Weapon> &weaponList);

  ///////////////
  /// Methods ///
  ///////////////
 
  /**
   * @brief Add a weapon to the main character's inventory.
   * @param weapon The weapon to add to the inventory.
   */
  void addWeapon(const Weapon &weapon);

    /**
      * @brief Perform an attack against an enemy using a specified weapon.
      * @param enemy The enemy to attack.
      * @param weapon The weapon to use for the attack.
      * @param battleLog Optional pointer to a vector of strings for logging battle events.
      *
      * This method calculates the total damage based on the weapon's hit chance
      * and hit repetitions, applies the damage to the enemy, and logs the attack
      * details if a battle log is provided.
      */
  void attack(Enemy &enemy, const Weapon &weapon,
              std::vector<std::string> *battleLog = nullptr);

  /**
   * @brief Check if the main character is dead (health is 0).
   * @return true if the main character's health is 0, false otherwise.
   */
  bool isDead();

  /**
   * @brief Prints a defeat message when the main character is defeated by an enemy.
   * @param enemy The enemy that defeated the main character.
   *
   */
  void defeatedMessage(Enemy &enemy);
};

#endif // MAIN_CHARACTER_H
