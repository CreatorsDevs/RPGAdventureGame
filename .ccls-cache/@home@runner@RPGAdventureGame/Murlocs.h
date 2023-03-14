#ifndef MURLOCS_H
#define MURLOCS_H

#include "Enemy.h"

class Murlocs : public Enemy
{
public:
  virtual int EnemyDoDamage() override;
  virtual bool EnemyTakeDamage(int damage) override;
  virtual bool EnemyDefense(int damage) override;
  virtual bool EnemyMove(int damage) override;

  static int GroundBash();
  static int SpeedDash();
  //Along with the above functions, all the other enemy member fucntions will be overrideen in murlocs.cpp
  static int constexpr murlocsHealth = 220;
  static int constexpr murlocsDamage = 30;
  static int constexpr murlocsHealing = 50;
};

#endif