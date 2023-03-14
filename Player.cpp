#include "Player.h"
#include "GameManager.h"
#include "HelperClass.h"
#include <iostream>
using namespace std;

Player::Player() {
  maxHealth = 100;
  health = maxHealth;
  meleeDamage = 10;
  rangedDamage = 5;
  minDamage = 5;
  maxDamage = 10;
  defense = 5;
  hasMap = true;
  specialItem = SpecialItems::None;
  usedBow = false;
}

int Player::GetHealth() { return health; }

bool Player::HasMap() { return hasMap; }

string Player::SpecialItemToString()
{
  string specialItemName;
  switch((int)specialItem)
  {
    case 1: specialItemName = "Sword"; break;
    case 2: specialItemName = "Shield"; break;
    case 3: specialItemName = "Armour"; break;
    case 4: specialItemName = "Bow"; break;
    default: specialItemName = "None"; break;
  }

  return specialItemName;
}

int Player::PlayerDoDamage() {
  int damage = 0;
  SpecialItems itemUsed = SpecialItems::None;
  if (specialItem != SpecialItems::None) {
    // Use Special Ability based on probabilty of 10%
    if (HelperClass::RandomNumberGenerator(10) <= 1)
      itemUsed = UseSpecialAbility(false);
  }

  if (itemUsed == SpecialItems::Sword) {
    // Critical Hit(Sword)
    cout << "Hero has used the sword and landed a critical hit!\n";
    damage = criticalHitDamage;
  } else if (itemUsed == SpecialItems::Armour) {
    // Life Steal(Armour)
    health += armourRecoveredHealth;
    health = HelperClass::Clamp(health, 0, maxHealth);
    damage =
        meleeDamage + HelperClass::RandomRangeGenerator(minDamage, maxDamage);
    cout << "Hero has used the Armour, health has been recovered by 30. \nBut alongside, he had used the Melee attack,\n";

  } else if (itemUsed == SpecialItems::Bow) {
    damage = rangedDamage + HelperClass::RandomRangeGenerator(minDamage, maxDamage);
    //Ranged Attack(Bow)
    cout << "Hero won't take the damage for next hit, since, he has used the Bow (Ranged attack),\n";
    usedBow = true;
  } else {
    damage =
        meleeDamage + HelperClass::RandomRangeGenerator(minDamage, maxDamage);
    cout << "Now, Hero has used the Melee attack,\n";
  }

  cout << "And, dealt the total of " << damage << " hp damage." << endl;

  return damage;
}

bool Player::PlayerTakeDamage(int dmg) {
  bool playerDied = false;

  if (usedBow) {
    cout << "Hero used the Bow(Ranged attack) previously so he won't take any "
            "damage this time.\n";
    usedBow = false;
    return playerDied;
  }

  health -= dmg;
  health = HelperClass::Clamp(health, 0, maxHealth);
  if (health <= 0) {
    playerDied = true;
    cout << "Very unfortunate! Hero has died.\n"
         << "You have lost the game!\n\n";
    HelperClass::DisplayGreenLine();
  } else {
    playerDied = false;
    cout << "Hero has taken the hit, deteriorated health is " << health
         << endl;
  }
  
  return playerDied;
}

bool Player::PlayerDefense(int dmg) {
  int deflectedDamage = 0;
  bool playerDied;
  SpecialItems itemUsed = SpecialItems::None;
  if (specialItem != SpecialItems::None) {
    // Use Special Ability based on probabilty of 10%
    if (HelperClass::RandomNumberGenerator(10) <= 1) {
      itemUsed = UseSpecialAbility(true);
    }
  }

  int def = defense;
  // Deflect all the damage if we used a shield.
  if (itemUsed == SpecialItems::Shield) {
    def = dmg;
    cout << "Hero has used the Shield that has blocked all the damage!" << endl;
  } else {
    deflectedDamage = HelperClass::Abs(dmg - def);
    health -= deflectedDamage;
  }

  if (health <= 0) {
    playerDied = true;
    cout << "Very unfortunate! Hero has died.\n"
         << "You have lost the game!\n\n";
    HelperClass::DisplayGreenLine();
  } else {
    playerDied = false;
    cout << "Hero has defended the attack by " << def
         << " hp amount, deteriorated health is " << health << endl;
  }

  return playerDied;
}

void Player::UpdateSpecialItems() {
  Level currentLevel = GameManager::GetInstance().GetLevel();

  // Give Special Items based on the currentLevel.
  switch (currentLevel.level) {
  case 3:
    specialItem = SpecialItems::Sword;
    break;
  case 4:
    specialItem = SpecialItems::Shield;
    break;
  case 5:
    specialItem = SpecialItems::Armour;
    break;
  case 6:
    specialItem = SpecialItems::Bow;
    break;
  default:
    specialItem = SpecialItems::None;
    break;
  }
}

void Player::LevelUpdate() 
{
  maxHealth += 25;
  meleeDamage += 5;
  rangedDamage += 5;
  defense += 5;
  health = maxHealth;
}

void Player::Reset()
{
  maxHealth = 100;
  health = maxHealth;
  meleeDamage = 10;
  rangedDamage = 5;
  minDamage = 5;
  maxDamage = 10;
  defense = 5;
  hasMap = true;
  specialItem = SpecialItems::None;
  usedBow = false;
}

Player::SpecialItems Player::UseSpecialAbility(bool isDefending) {
  SpecialItems itemUsed = SpecialItems::None;
  if (isDefending) {
    // Use Shield if available.
    if (specialItem >= SpecialItems::Shield)
      itemUsed = SpecialItems::Shield;
  } else {
    // Use all the attack abilities.
    int level = GameManager::GetInstance().GetLevel().level;
    int probability =
        HelperClass::RandomNumberGenerator(level - level > 3 ? 3 : 2);

    switch (probability) {
    case 1:
      itemUsed = SpecialItems::Sword;
      break; // Deal Critial Hit(Sword)
    case 2:
      itemUsed = SpecialItems::Armour;
      break; // Life Steal(Armour)
    case 3:
      itemUsed = SpecialItems::Bow;
      break; // Ranged Attack!
    default:
      break;
    }
  }

  return itemUsed;
}