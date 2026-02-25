#ifndef RAIDER_H
#define RAIDER_H

#include "Enemies/Enemy.h"

/**
 * @brief A raider enemy type.
 *
 * Raider currently has no additional members beyond Enemy but exists
 * to allow future specialization.
 */
class Raider : public Enemy {
public:
  // Inherit constructors from Enemy and override type getter
  using Enemy::Enemy;

  std::string getType() const override;
};

#endif // !RAIDER_H
