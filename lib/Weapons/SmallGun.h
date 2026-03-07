#ifndef SMALLGUN_H
#define SMALLGUN_H

#include "Weapon.h"

/**
 * @brief Small Guns weapon base class for pistols, rifles, and other firearms.
 *
 * SmallGun currently shares Weapon's behavior but may be extended later.
 */
class SmallGun : public Weapon {
  // Inherit Weapon's constructors
  using Weapon::Weapon;

  ///////////////
  /// Methods ///
  ///////////////

  std::string getType() const override;
};

#endif // SMALLGUN_H
