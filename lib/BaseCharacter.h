#ifndef BASE_CHARARACTER_H
#define BASE_CHARARACTER_H

#include <cstdint>
#include <string>

/**
 * @brief BaseCharacter class represents the common attributes and behaviors of characters in the game.
 * It serves as a base class for both Player and Enemy classes, encapsulating shared properties like
 * name, health, max health, and bottlecaps. It also provides a method to apply damage to the character.
 */
class BaseCharacter {
protected:
  std::string name;
  uint16_t health;
  uint16_t maxHealth;
  uint16_t bottlecaps;

public:
  BaseCharacter(std::string name, uint16_t maxHealth, uint16_t bottlecaps);

  virtual ~BaseCharacter() = default;

  /**
   * @brief Apply damage to this character, reducing health accordingly.
   * @param damage Amount of damage to apply (non-negative).
   */
  void takeDamage(uint16_t damage);

  // Getters
  const std::string &getName() const;
  uint16_t getHealth() const;
  uint16_t getBottlecaps() const;
  uint16_t getMaxHealth() const;

  // Setters
  void setName(const std::string &name);
  void setHealth(uint16_t health);
  void setBottlecaps(uint16_t bottlecaps);
  void setMaxHealth(uint16_t maxHealth);

};

#endif
