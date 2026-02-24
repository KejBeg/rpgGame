#ifndef WEAPON_H
#define WEAPON_H

#include <iostream>
#include <string>
#include <list>

using std::string;

class Weapon {
private:
  string name;
  int damage;
  int hitChance;

  public:
  const string& getName() const;
  int getDamage() const;
  int getHitChance() const;

  void setName(const string& n);
  void setDamage(int d);
  void setHitChance(int hc);
};

#endif // !WEAPON_H
