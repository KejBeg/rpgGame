#ifndef MAIN_CHARACTER_H
#define MAIN_CHARACTER_H

#include "BaseCharacter.h"
#include "Weapons/Weapon.h"
#include <cstdint>
#include <list>
#include <string>
#include <vector>

class Enemy; // forward declare to avoid circular include

class MainCharacter: public BaseCharacter {
private:
  std::list<Weapon> weaponList;

public:
  /**
   * @brief Construct a new MainCharacter object.
   */
  MainCharacter(std::string name, uint16_t maxHealth, uint16_t bottlecaps,
                std::list<Weapon> weaponList);

  const std::list<Weapon> &getWeaponList() const;
  std::list<Weapon> &getWeaponList();

  void setWeaponList(const std::list<Weapon> &weaponList);

  void attack(Enemy &enemy, const Weapon &weapon,
              std::vector<std::string> *battleLog = nullptr);

  bool isDead();

  void defeated(Enemy &enemy);

};

#endif // MAIN_CHARACTER_H
