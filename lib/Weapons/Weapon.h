#ifndef WEAPON_H
#define WEAPON_H

#include <cstdint>
#include <string>

/**
 * @brief Represents a weapon that can be used by characters in the game.
 *
 * Each weapon has a unique ID, name, damage value, hit chance, and number of
 * hit repetitions.
 */
class Weapon {
private:
  uint16_t id;
  std::string name;
  uint16_t damage;
  uint8_t hitChance;
  uint8_t hitReps;

public:
  ////////////////////
  /// Constructors ///
  ////////////////////

  /**
   * @brief Construct a new Weapon instance.
   * @param name Weapon name.
   * @param damage Damage amount.
   * @param hitChance Hit chance value.
   * @param hitReps Number of hit repetitions.
   */
  Weapon(uint16_t id, std::string name, uint16_t damage, uint8_t hitChance,
         uint8_t hitReps);

  /**
   * @brief Construct a new Weapon with default values.
   */
  Weapon();

  virtual ~Weapon() = default;

  ///////////////
  /// Getters ///
  ///////////////

  /**
   * @brief Get the weapon's unique identifier.
   * @return uint16_t Weapon ID.
   */
  uint16_t getId() const;

  /**
   * @brief Get the weapon's name.
   * @return std::string Weapon name.
   */
  std::string getName() const;

  /**
   * @brief Get the damage value of the weapon.
   * @return uint16_t Damage amount.
   */
  uint16_t getDamage() const;

  /**
   * @brief Get the base hit chance of the weapon (0-255).
   * @return uint8_t Hit chance value.
   */
  uint8_t getHitChance() const;

  /**
   * @brief Get the number of hit repetitions this weapon performs.
   * @return uint8_t Hit repetitions.
   */
  uint8_t getHitReps() const;

  ///////////////
  /// Setters ///
  ///////////////
  
  /**
   * @brief Set the weapon's unique identifier.
   * @param id New ID to assign to the weapon.
   */
  void setId(uint16_t id);

  /**
   * @brief Set the weapon's name.
   * @param name New name to assign to the weapon.
   */
  void setName(std::string name);

  /**
   * @brief Set the weapon's damage value.
   * @param damage Damage amount.
   */
  void setDamage(uint16_t damage);

  /**
   * @brief Set the weapon's hit chance.
   * @param hitChance Hit chance value (0-255).
   */
  void setHitChance(uint8_t hitChance);

  /**
   * @brief Set the weapon's hit repetitions.
   * @param hitReps Number of hit repetitions.
   */
  void setHitReps(uint8_t hitReps);


  ///////////////
  /// Methods ///
  ///////////////

  /**
   * @brief Get the type of the weapon (e.g., "Big Gun", "Pistol", "Rifle").
   * @return std::string Type of the weapon.
   */
  virtual std::string getType() const;
};

#endif // !WEAPON_H
