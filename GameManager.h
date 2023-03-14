#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include "Enemy.h"
#include "Player.h"
#include <memory>
#include <vector>

struct Level {
  int level;
  int numberOfEnemies;
  Level(int _lvl) : level(_lvl), numberOfEnemies(_lvl) {}
};

class GameManager {
public:
  static GameManager &GetInstance() {
    static GameManager instance;
    return instance;
  }
  void GameTitle();
  void Instructions();
  void Update();
  static Level GetLevel() { return s_Level; }
  static void SetLevel(Level level) { s_Level = level; }

private:
  // For Member Functions
  GameManager();
  GameManager(const GameManager &) = delete;
  GameManager &operator=(const GameManager &) = delete;
  void SetEnemy();
  bool PlayerAction();
  void GameLoop();

private:
  // For Members
  static Level s_Level;
  std::unique_ptr<Player> m_Player;
  std::unique_ptr<Enemy> m_Enemy;
};

#endif // GAMEMANAGER_H