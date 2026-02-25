
#ifndef SUPERMUTANT_H
#define SUPERMUTANT_H

#include "Enemies/Enemy.h"

/**
 * @brief A stronger variant of Enemy with modified stats/behavior.
 *
 * SuperMutant currently has no additional members beyond Enemy but exists
 * to allow future specialization.
 */
class SuperMutant : public Enemy {
public:
  std::string getType() const override;

  using Enemy::Enemy;
};

#endif // !SUPERMUTANT_H
