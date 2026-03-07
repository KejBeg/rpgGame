
#ifndef ENERGYWEAPON_H
#define ENERGYWEAPON_H

#include "Weapon.h"

/**
 * @brief EnergyWeapon category for energy-based firearms.
 *
 * EnergyWeapon currently shares Weapon's behavior but may be extended later.
 */
class EnergyWeapon : public Weapon {
  // Inherit Weapon's constructors
  using Weapon::Weapon;

  ///////////////
  /// Methods ///
  ///////////////
  
  std::string getType() const override;
};

#endif // ENERGYWEAPON_H
