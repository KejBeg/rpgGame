#ifndef BASE_CHARARACTER_H
#define BASE_CHARARACTER_H

#include <cstdint>
#include <string>

/**
 * @brief BaseCharacter class represents the common attributes and behaviors of
 * characters in the game. It serves as a base class for both Player and Enemy
 * classes, encapsulating shared properties like name, health, max health, and
 * bottlecaps. It also provides a method to apply damage to the character.
 */
class BaseCharacter {
protected:
  std::string name;
  uint16_t health;
  uint16_t maxHealth;
  uint16_t bottlecaps;

public:
  ////////////////////
  /// Constructors ///
  ////////////////////

  /**
   * @brief Construct a new BaseCharacter object with specified attributes.
   * @param name Name of the character.
   * @param maxHealth Maximum health value for the character.
   * @param bottlecaps Initial bottlecap count for the character.
   * The current health is initialized to the maximum health value.
   */
  BaseCharacter(std::string name, uint16_t maxHealth, uint16_t bottlecaps);

  ///////////////
  /// Getters ///
  ///////////////
  /**
   * @brief Get the name of the character.
   * @return const std::string& Character's name.
   */
  const std::string &getName() const;

    /**
    * @brief Get the current health of the character.
    * @return uint16_t Current health value.
    */
  uint16_t getHealth() const;

  /**
   * @brief Get the current bottlecap count of the character.
   * @return uint16_t Current bottlecap count.
   */
  uint16_t getBottlecaps() const;

  /**
   * @brief Get the maximum health of the character.
   * @return uint16_t Maximum health value.
   */
  uint16_t getMaxHealth() const;

  ///////////////
  /// Setters ///
  ///////////////

  /**
   * @brief Set the name of the character.
   * @param name New name for the character.
   */
  void setName(const std::string &name);

  /**
   * @brief Set the current health of the character.
   * @param health New health value to assign to the character.
   */
  void setHealth(uint16_t health);

  /**
   * @brief Set the current bottlecap count of the character.
   * @param bottlecaps New bottlecap count to assign to the character.
   */
  void setBottlecaps(uint16_t bottlecaps);

  /**
   * @brief Set the maximum health of the character.
   * @param maxHealth New maximum health value to assign to the character.
   */
  void setMaxHealth(uint16_t maxHealth);

  ///////////////
  /// Methods ///
  ///////////////

  /**
   * @brief Apply damage to this character, reducing health accordingly.
   * @param damage Amount of damage to apply (non-negative).
   */
  void takeDamage(uint16_t damage);
};

#endif
