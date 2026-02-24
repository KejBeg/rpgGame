#include "Enemy.h"
#include <algorithm>

const std::string &Enemy::getName() const { return name; }
int Enemy::getHealth() const { return health; }
int Enemy::getBottlecaps() const { return bottlecaps; }
const Weapon &Enemy::getCurrentWeapon() const { return currentWeapon; }
Weapon &Enemy::getCurrentWeapon() { return currentWeapon; }

void Enemy::setName(const std::string &n) { name = n; }
void Enemy::setHealth(int h) { health = std::clamp(h, 0, 100); }
void Enemy::setBottlecaps(int b) { bottlecaps = std::max(0, b); }
void Enemy::setCurrentWeapon(const Weapon &w) { currentWeapon = w; }
