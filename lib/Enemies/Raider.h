#ifndef RAIDER_H
#define RAIDER_H

#include "Enemies/Enemy.h"

/**
 * @brief A Raider enemy type.
 *
 * Raider currently shares Enemy's behavior but may be extended later.
 */
class Raider : public Enemy {
public:
  // Inherit Enemy's constructors
  using Enemy::Enemy;

  ///////////////
  /// Methods ///
  ///////////////

  std::string getType() const override;
};

#endif // !RAIDER_H
