
#ifndef SUPERMUTANT_H
#define SUPERMUTANT_H

#include "Enemies/Enemy.h"

/**
 * @brief A SuperMutant enemy type.
 *
 * SuperMutant currently shares Enemy's behavior but may be extended later.
 */
class SuperMutant : public Enemy {
public:
  // Inherit Enemy's constructors
  using Enemy::Enemy;

  ///////////////
  /// Methods ///
  ///////////////

  std::string getType() const override;
};

#endif // !SUPERMUTANT_H
