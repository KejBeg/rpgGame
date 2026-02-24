#ifndef CHARACTER_H
#define CHARACTER_H

#include <iostream>
#include <list>
#include "Weapon.h"

class Weapon;

using std::string;
using std::list;

class Character {
private:
  string name;
  int health;
  int bottlecaps;

  list<Weapon> weaponList;
  int currentWeapon;
public:
  const string& getName() const;
  int getHealth() const;
  int getBottlecaps() const;
  const list<Weapon>& getWeaponList() const;
  list<Weapon>& getWeaponList();
  int getCurrentWeapon() const;

  void setName(const string& n);
  void setHealth(int h);
  void setBottlecaps(int b);
  void setWeaponList(const list<Weapon>& wl);
  void setCurrentWeapon(int idx);
};

#endif // !CHARACTER_H
