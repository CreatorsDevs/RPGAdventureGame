#ifndef PLAYER_H
#define PLAYER_H
#include <string>

class Player {
public:
  Player();
  int GetHealth();
  int PlayerDoDamage();
  bool PlayerTakeDamage(int);
  bool PlayerDefense(int);
  void UpdateSpecialItems();
  void LevelUpdate();
  void Reset();
  bool HasMap();
  std::string SpecialItemToString();

private:
  enum SpecialItems { None, Sword, Shield, Armour, Bow } specialItem;
  int health;
  int maxHealth;
  int meleeDamage;
  int rangedDamage;
  int minDamage;
  int maxDamage;
  int defense;
  bool hasMap;
  bool usedBow;

  SpecialItems UseSpecialAbility(bool isDefending);
  static int constexpr criticalHitDamage = 50;
  static int constexpr armourRecoveredHealth = 30;
};

#endif // PLAYER_H