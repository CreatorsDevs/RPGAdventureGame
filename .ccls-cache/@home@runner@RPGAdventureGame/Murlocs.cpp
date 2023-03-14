#include "Murlocs.h"
#include "GameManager.h"
#include "HelperClass.h"
#include <iostream>
using namespace std;

//Special ability of murlocs ( Ground Bash )
int Murlocs::GroundBash() {
  int damage = Murlocs::murlocsDamage * 3;
  cout << "Murlocs has used one of his special ability (GroundBash) and landed "
          "a huge strike of "
       << damage << " hp damage\n";
  return damage;
}

//Special ability of murlocs ( Speed Dash )
int Murlocs::SpeedDash() {
  int damage = Murlocs::murlocsDamage * 2;
  cout << "Murlocs has used one of his special ability (SpeedDash) and dealt a "
          "swift strike of "
       << damage << " hp damage\n";
  return damage;
}


int Murlocs::EnemyDoDamage() {
  int randomConditionValue = HelperClass::RandomNumberGenerator(5);
  if (randomConditionValue <= 3) {
    int damage = HelperClass::RandomRangeGenerator(minDamage, maxDamage) +
                 Murlocs::murlocsDamage;
    cout << "Murlocs has dealt the total of " << damage << " hp damage."
         << endl;
    return damage;
  } else {
    int subRandomConditionValue = HelperClass::RandomNumberGenerator(5);
    if (randomConditionValue <= 3) {
      return (Murlocs::GroundBash());
    } else {
      return (Murlocs::SpeedDash());
    }
  }
}

bool Murlocs::EnemyTakeDamage(int dmg) {

  bool enemyHasDied = false;
  health -= dmg;
  health = HelperClass::Clamp(health, 0, maxHealth);
  if (health <= 0) {
    enemyHasDied = true;
    hasDied = true;
    cout << "\nIt's Over! Murlocs died!\n" << endl;
    return hasDied;
  } else {
    enemyHasDied = false;
    cout << "Murlocs deteriorted health is " << health << endl;
    return enemyHasDied;
  }
}

bool Murlocs::EnemyDefense(int dmg) {
  int randomConditionValue = HelperClass::RandomNumberGenerator(5);
  if (randomConditionValue <= 3) {
    bool enemyHasDied = false;
    int enemyDeflectedDamage = 0;
    int defense =
        HelperClass::RandomRangeGenerator(defenseRange[0], defenseRange[1]);
    enemyDeflectedDamage = HelperClass::Abs(dmg - defense);
    health -= enemyDeflectedDamage;
    if (health <= 0) {
      enemyHasDied = true;
      cout << "\nIt's Over! Murlocs died!\n" << endl;
      return enemyHasDied;
    } else {
      enemyHasDied = false;
      cout << "Murlocs defended the attack by " << defense
           << " hp amount, deteriorated health is " << health << endl;
      return enemyHasDied;
    }
  } else {
    bool enemyHasDied = false;
    if (health <= 0) {
      enemyHasDied = true;
      cout << "\nIt's Over! Murlocs died!\n" << endl;      
      return enemyHasDied;
    } else {
      enemyHasDied = false;
      health += Murlocs::murlocsHealing;
      health = HelperClass::Clamp(health, 0, maxHealth);
      //Special ability of murlocs ( Health Regen )
      cout << "Murlocs has used one of his special ability (HealthRegen) and "
              "recovered "
           << health << " hp.\n";
      return enemyHasDied;
    }
  }
}

bool Murlocs::EnemyMove(int dmg) {
  int randomConditionValue = HelperClass::RandomNumberGenerator(5);
  bool hasDied =
      randomConditionValue <= 3 ? EnemyTakeDamage(dmg) : EnemyDefense(dmg);
  return hasDied;
}