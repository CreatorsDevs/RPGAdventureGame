#include "Enemy.h"
#include "GameManager.h"
#include "HelperClass.h"
#include <iostream>
#include <string>

using namespace std;

Enemy::Enemy() {
  maxHealth = 20;
  health = maxHealth;
  minDamage = 5;
  maxDamage = 10;
  hasDied = false;
}

int Enemy::EnemyDoDamage() {
  int numberOfEnemies = GameManager::GetLevel().numberOfEnemies;
  int damage =
      HelperClass::RandomRangeGenerator(minDamage, maxDamage) * numberOfEnemies;
  string enemyString = numberOfEnemies > 1 ? "Enemies have " : "Enemy has ";
  cout << enemyString + "dealt the total of " << damage << " hp damage."
       << endl;
  return damage;
}

bool Enemy::EnemyTakeDamage(int dmg) {
  bool enemyHasDied = false;
  health -= dmg;
  health = HelperClass::Clamp(health, 0, maxHealth);
  if (health <= 0) {
    enemyHasDied = true;
    hasDied = true;
    if (GameManager::GetLevel().level > 1)
      cout << "\nAll Enemies died!\n\n";
    else
      cout << "\nEnemy died!\n\n";
    return hasDied;
  } else {
    enemyHasDied = false;
    if (GameManager::GetLevel().level > 1)
      cout << "Enemies deteriorated health is " << health << endl;
    else
      cout << "Enemy's deteriorated health is " << health << endl;
    return enemyHasDied;
  }
}

bool Enemy::EnemyDefense(int dmg) {
  bool enemyHasDied = false;
  int enemyDeflectedDamage = 0;
  int defense =
      HelperClass::RandomRangeGenerator(defenseRange[0], defenseRange[1]);
  enemyDeflectedDamage = HelperClass::Abs(dmg - defense);
  health -= enemyDeflectedDamage;
  if (health <= 0) {
    enemyHasDied = true;
    if (GameManager::GetLevel().level > 1)
      cout << "\nAll Enemies died!\n\n";
    else
      cout << "\nEnemy died!\n\n";    
    return enemyHasDied;
  } else {
    enemyHasDied = false;
    if (GameManager::GetLevel().level > 1)
      cout << "Enemies defended the attack by " << defense
         << " hp amount, deteriorated health is " << health << endl;
    else
      cout << "Enemy defended the attack by " << defense
         << " hp amount, deteriorated health is " << health << endl;
    
    return enemyHasDied;
  }
}

bool Enemy::EnemyMove(int dmg) {
  int randomConditionValue = HelperClass::RandomNumberGenerator(5);
  bool hasDied =
      randomConditionValue <= 3 ? EnemyTakeDamage(dmg) : EnemyDefense(dmg);
  return hasDied;
}

void Enemy::SetHealth(int health) {
  this->maxHealth = health;
  this->health = maxHealth;
}