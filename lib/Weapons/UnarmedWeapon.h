
#ifndef UNARMEDWEAPON_H
#define UNARMEDWEAPON_H

#include "Weapon.h"

/**
 * @brief Unarmed weapon type (fists, basic melee) derived from Weapon.
 *
 * UnarmedWeapon currently shares Weapon's behavior but may be extended later.
 */
class UnarmedWeapon : public Weapon {
  // Inherit Weapon's constructors
  using Weapon::Weapon;

  ///////////////
  /// Methods ///
  ///////////////
  std::string getType() const override;
};

#endif // UNARMEDWEAPON_H
