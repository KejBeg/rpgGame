#ifndef GHOUL_H
#define GHOUL_H

#include "Enemies/Enemy.h"

/**
 * @brief A basic Ghoul enemy type.
 *
 * Ghoul currently shares Enemy's behavior but may be extended later.
 */
class Ghoul : public Enemy {
public:
  using Enemy::Enemy;

  std::string getType() const override;
};

#endif // !GHOUL_H
