#ifndef CHARACTER_H
#define CHARACTER_H

#include <string>
#include <list>
#include "Weapons/Weapon.h"

class Enemy; // forward declare to avoid circular include


class Character {
private:
  std::string name;
  int health;
  int bottlecaps;

  std::list<Weapon> weaponList;
public:
  /**
   * @brief Construct a new Character object.
   * @param name Character's name.
   * @param health Initial health (0-100).
   * @param bottlecaps Initial bottlecap count (non-negative).
   * @param weaponList Initial list of weapons.
   */
  Character(std::string, int, int, std::list<Weapon>);

  /**
   * @brief Get the character's name.
  * @return const std::string& Reference to the stored name.
   */
  const std::string& getName() const;

  /**
   * @brief Get the character's current health.
   * @return int Health value (0-100).
   */
  int getHealth() const;

  /**
   * @brief Get the character's bottlecap count.
   * @return int Non-negative bottlecaps count.
   */
  int getBottlecaps() const;

  /**
   * @brief Access the weapon list (read-only).
  * @return const std::list<Weapon>& Reference to internal weapon list.
   */
  const std::list<Weapon>& getWeaponList() const;

  /**
   * @brief Access the weapon list for modification.
  * @return std::list<Weapon>& Reference to internal weapon list.
   */
  std::list<Weapon>& getWeaponList();

  /**
   * @brief Set the character's name.
   * @param name New name to assign.
   */
  void setName(const std::string& name);

  /**
   * @brief Set the character's health.
   * @param health New health value; implementation may clamp this value.
   */
  void setHealth(int health);

  /**
   * @brief Set the character's bottlecaps.
   * @param bottlecaps Non-negative bottlecap count.
   */
  void setBottlecaps(int bottlecaps);

  /**
   * @brief Replace the character's weapon list.
   * @param weaponList New weapon list to copy.
   */
  void setWeaponList(const std::list<Weapon>& weaponList);

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
