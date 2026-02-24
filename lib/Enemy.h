#ifndef ENEMY_H
#define ENEMY_H

#include <iostream>
#include <list>
#include "Weapon.h"


using std::string;
using std::list;

class Enemy {
private:
  string name;
  int health;
  int bottlecaps;


  Weapon currentWeapon;
public:
  const string& getName() const;
  int getHealth() const;
  int getBottlecaps() const;
  const Weapon& getCurrentWeapon() const;
  Weapon& getCurrentWeapon();

  void setName(const string& n);
  void setHealth(int h);
  void setBottlecaps(int b);
  void setCurrentWeapon(const Weapon& w);
};

#endif // !ENEMY_H
