#include "Character.h"
#include <algorithm>

const std::string& Character::getName() const { return name; }
int Character::getHealth() const { return health; }
int Character::getBottlecaps() const { return bottlecaps; }
const std::list<Weapon>& Character::getWeaponList() const { return weaponList; }
std::list<Weapon>& Character::getWeaponList() { return weaponList; }
int Character::getCurrentWeapon() const { return currentWeapon; }

void Character::setName(const std::string& n) { name = n; }
void Character::setHealth(int h) { health = std::clamp(h, 0, 100); }
void Character::setBottlecaps(int b) { bottlecaps = std::max(0, b); }
void Character::setWeaponList(const std::list<Weapon>& wl) { weaponList = wl; }
void Character::setCurrentWeapon(int idx) { currentWeapon = idx; }
