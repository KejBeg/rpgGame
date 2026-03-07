#ifndef BIGGUNS_H
#define BIGGUNS_H

#include "Weapon.h"

/**
 * @brief BigGuns weapon category for heavy firearms.
 *
 * BigGuns currently shares Weapon's behavior but may be extended later.
 */
class BigGun : public Weapon {
  // Inherit Weapon's constructors
  using Weapon::Weapon;

  ///////////////
  /// Methods ///
  ///////////////

  std::string getType() const override;
};

#endif // BIGGUNS_H
