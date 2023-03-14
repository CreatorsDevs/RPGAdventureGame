#ifndef ENEMY_H
#define ENEMY_H

class Enemy {
protected:
  int health;
  int maxHealth = 20;
  int damage;
  int minDamage;
  int maxDamage;
  int defenseRange[2] = {4, 8};
  bool hasDied;

public:
  Enemy();
  virtual int EnemyDoDamage();
  virtual bool EnemyTakeDamage(int damage);
  virtual bool EnemyDefense(int damage);
  virtual bool EnemyMove(int damage);
  int GetHealth() const { return health; }
  void SetHealth(int health);
};

#endif // ENEMY_H