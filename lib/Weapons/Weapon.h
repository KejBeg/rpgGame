#ifndef WEAPON_H
#define WEAPON_H

#include <cstdint>
#include <string>


class Weapon {
private:
  uint16_t id;
  std::string name;
  uint16_t damage;
  uint8_t hitChance;
  uint8_t hitReps;

public:
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

  /**
   * @brief Construct a new Weapon instance.
   * @param name Weapon name.
   * @param damage Damage amount.
   * @param hitChance Hit chance value.
   * @param hitReps Number of hit repetitions.
   */
  Weapon(uint16_t id, std::string name, uint16_t damage, uint8_t hitChance, uint8_t hitReps);
  // Backwards-compatible constructor (no id) — assigns id = 0
  Weapon(std::string name, uint16_t damage, uint8_t hitChance, uint8_t hitReps);

};

#endif // !WEAPON_H
