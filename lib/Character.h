#ifndef CHARACTER_H
#define CHARACTER_H

#include "Weapons/Weapon.h"
#include <cstdint>
#include <list>
#include <string>

class Enemy; // forward declare to avoid circular include

class Character {
private:
  std::string name;

  uint16_t health;
  uint16_t maxHealth;
  uint16_t bottlecaps;

  std::list<Weapon> weaponList;

public:
  /**
   * @brief Construct a new Character object.
   * @param name Character's name.
   * @param maxHealth Maximum health value.
   * @param bottlecaps Initial bottlecap count (non-negative).
   * @param weaponList Initial list of weapons.
   */
  Character(std::string name, uint16_t maxHealth, uint16_t bottlecaps,
            std::list<Weapon> weaponList);

  /**
   * @brief Get the character's name.
   * @return const std::string& Reference to the stored name.
   */
  const std::string &getName() const;

  /**
   * @brief Get the character's current health.
   * @return uint16_t Health value (0-100).
   */
  uint16_t getHealth() const;

  /**
   * @brief Get the character's bottlecap count.
   * @return uint16_t Non-negative bottlecaps count.
   */
  uint16_t getBottlecaps() const;

  /**
   * @brief Get the character's maximum health.
   * @return uint16_t Maximum health value.
   */
  uint16_t getMaxHealth() const;

  /**
   * @brief Set the character's maximum health.
   * @param maxHealth New maximum health value.
   */
  void setMaxHealth(uint16_t maxHealth);

  /**
   * @brief Access the weapon list (read-only).
   * @return const std::list<Weapon>& Reference to internal weapon list.
   */
  const std::list<Weapon> &getWeaponList() const;

  /**
   * @brief Access the weapon list for modification.
   * @return std::list<Weapon>& Reference to internal weapon list.
   */
  std::list<Weapon> &getWeaponList();

  /**
   * @brief Set the character's name.
   * @param name New name to assign.
   */
  void setName(const std::string &name);

  /**
   * @brief Set the character's health.
   * @param health New health value; implementation may clamp this value.
   */
  void setHealth(uint16_t health);

  /**
   * @brief Set the character's bottlecaps.
   * @param bottlecaps Non-negative bottlecap count.
   */
  void setBottlecaps(uint16_t bottlecaps);

  /**
   * @brief Replace the character's weapon list.
   * @param weaponList New weapon list to copy.
   */
  void setWeaponList(const std::list<Weapon> &weaponList);

  /**
   * @brief Attack an enemy using the specified weapon.
   * @param enemy The enemy to attack (read-only reference).
   * @param weapon The weapon used for the attack (read-only reference).
   */
  /**
   * @brief Attack an enemy using the specified weapon.
   * @param enemy The enemy to attack (may be modified).
   * @param weapon The weapon used for the attack (read-only reference).
   */
  void attack(Enemy &enemy, const Weapon &weapon);

  /**
   * @brief Apply damage to this character, reducing health.
   * @param damage Amount of damage to apply (non-negative).
   */
  void takeDamage(uint16_t damage);
};

#endif // !CHARACTER_H
