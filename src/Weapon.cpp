#include "Weapon.h"

const std::string& Weapon::getName() const { return name; }
int Weapon::getDamage() const { return damage; }
int Weapon::getHitChance() const { return hitChance; }

void Weapon::setName(const std::string& n) { name = n; }
void Weapon::setDamage(int d) { damage = d; }
void Weapon::setHitChance(int hc) { hitChance = hc; }
