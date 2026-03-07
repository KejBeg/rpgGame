#include "BaseCharacter.h"

#include <algorithm>

BaseCharacter::BaseCharacter(std::string name, uint16_t maxHealth, uint16_t bottlecaps) {
  this->name = std::move(name);
  this->health = maxHealth;
  this->maxHealth = maxHealth;
  this->bottlecaps = bottlecaps;
}

const std::string &BaseCharacter::getName() const { return name; }
uint16_t BaseCharacter::getHealth() const { return health; }
uint16_t BaseCharacter::getBottlecaps() const { return bottlecaps; }
uint16_t BaseCharacter::getMaxHealth() const { return maxHealth; }

void BaseCharacter::setName(const std::string &name) { this->name = name; }
void BaseCharacter::setHealth(uint16_t health) {
  if (health > maxHealth) {
    this->health = maxHealth;
  } else {
    this->health = health;
  }
}
void BaseCharacter::setBottlecaps(uint16_t bottlecaps) { this->bottlecaps = bottlecaps; }
void BaseCharacter::setMaxHealth(uint16_t maxHealth) { this->maxHealth = maxHealth; }

void BaseCharacter::takeDamage(uint16_t damage) {
  // prevent underflow when subtracting
  uint16_t newHealth = (damage >= health) ? 0 : static_cast<uint16_t>(health - damage);
  setHealth(newHealth);
}
