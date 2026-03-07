
#ifndef MELEEWEAPON_H
#define MELEEWEAPON_H

#include "Weapon.h"

/**
 * @brief Melee weapon base class for close-range weapons.
 *
 * MeleeWeapon currently shares Weapon's behavior but may be extended later with
 */
class MeleeWeapon : public Weapon {
  // Inherit Weapon's constructors
  using Weapon::Weapon;

  ///////////////
  /// Methods ///
  ///////////////
  std::string getType() const override;
};

#endif // MELEEWEAPON_H
