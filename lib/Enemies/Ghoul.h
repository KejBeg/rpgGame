#ifndef GHOUL_H
#define GHOUL_H

#include "Enemies/Enemy.h"

/**
 * @brief A Ghoul enemy type.
 *
 * Ghoul currently shares Enemy's behavior but may be extended later.
 */
class Ghoul : public Enemy {
public:
  // Inherit Enemy's constructors
  using Enemy::Enemy;

  ///////////////
  /// Methods ///
  ///////////////

  std::string getType() const override;
};

#endif // !GHOUL_H
