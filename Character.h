#ifndef CHARACTER_H
#define CHARACTER_H

#include <iostream>
#include <list>
#include "Weapon.h"

using namespace std;

class Character {
private:
  string name;
  int health;
  int bottlecaps;

  list<Weapon> weaponList;
  int currentWeapon;
public:
};

#endif // !CHARACTER_H
