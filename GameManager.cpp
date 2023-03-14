#include "GameManager.h"
#include "HelperClass.h"
#include "Murlocs.h"
#include "Player.h"
#include <iomanip>
#include <iostream>
using namespace std;

Level GameManager::s_Level = {1};

GameManager::GameManager() {
  m_Player = std::make_unique<Player>();
  SetEnemy();
}

void GameManager::GameTitle() {
  cout << '!' << setfill('+') << setw(111) << '!' << endl;
  cout << '+' << setfill(' ') << setw(111) << '+' << endl;
  cout << '+' << setfill(' ') << setw(111) << '+' << endl;
  cout << '+' << setfill(' ') << "\033[32m" << string(47, ' ') << setw(63)
       << left << "RPG Adventure!"
       << "\033[0m" << '+' << endl;
  cout << '+' << setfill(' ') << setw(111) << right << '+' << endl;
  cout << '+' << setfill(' ') << setw(111) << '+' << endl;
  cout << '!' << setfill('+') << setw(111) << '!' << endl;
}

void GameManager::Instructions() {
  cout << "\033[34m"
       << "\n\nABOUT THE GAME\n\n"
       << "\033[0m";

  cout << "- Our hero's village has been captured by a monster"
       << "\033[31m"
       << " Murlocs.\n"
       << "\033[0m"
       << "- You being the hero is the last hope of your people.\n"
       << "  Kill the monster king and save your people!\n"
       << "- There will be 5 levels that you have to win against different "
          "enemies before entering the last level (level 6)\n"
       << "  Where you will battle against the monster king!\n"
       << "  Also, you gonna unlock different special items after winning each "
          "level which will help you in the final battle!\n"
       << "- You as a hero has the abilities to do melee/range attack and "
          "defence!\n"
       << "  Also, there will be special abilities for you which will keep "
          "getting unlocked as levels progress.\n"
       << "  Depending upon the probability of activation of these special "
          "abilities - \n"
       << "  The abilities will get triggered when you chooses to do an "
          "attack.\n";

  cout << "\033[34m"
       << "\n\nNOW, LET'S GET READY TO ANNIHILATE THESE MONSTERS!\n\n"
       << "\033[0m";
}

void GameManager::Update() {
  char playOrExit;
  do {
    // Reset
    s_Level = {1};
    m_Player->Reset();
    SetEnemy();

    cout << "Press P to play the game or any key to exit...\n";
    cin >> playOrExit;
    HelperClass::ClearBadBits();
    cout << endl;
    if(playOrExit == 'p' || playOrExit == 'P'){
      cout << "You have entered the level " << s_Level.level << " (you have to fight only " 
           << s_Level.numberOfEnemies << " enemy)!\n"  
           << "Hero's health is: " << m_Player->GetHealth() << " And, enemy health is: " << m_Enemy->GetHealth() << endl;
      if(m_Player->HasMap())
        cout << "Also, Hero has got the map!" << endl;
    GameManager::GameLoop();
    }
    else{
      cout << "Thanks for playing,\n" 
         << "Come Back soon!" << endl;
    }
    

  } while (playOrExit == 'p' || playOrExit == 'P');
}

bool GameManager::PlayerAction() {
  char userInput;
  bool playerDied;
  bool enemyHasDied;
  int inputCounter = 0;
  bool inputValid = false;
  do {
    if (inputCounter > 0 && !inputValid)
      cout << "Invalid Input ..\n\n";

    cout << "Press A to Attack OR Press D to Defend:\n";
    cin >> userInput;
    HelperClass::ClearBadBits();
    cout << endl;
    if (userInput == 'A' || userInput == 'a') {
      enemyHasDied = m_Enemy->EnemyMove(m_Player->PlayerDoDamage());
      if (!enemyHasDied) {
        playerDied = m_Player->PlayerTakeDamage(m_Enemy->EnemyDoDamage());
        inputValid = true;
        return playerDied;
      } else {        
        inputValid = true;
      }

    } else if (userInput == 'D' || userInput == 'd') {
      playerDied = m_Player->PlayerDefense(m_Enemy->EnemyDoDamage());
      inputValid = true;
      return playerDied;
    } else {
      inputValid = false;
    }
    inputCounter++;

    // Increase The Level
    if (enemyHasDied) 
    {
      // Level Changed!
      s_Level = {++s_Level.level};      
      
      SetEnemy();

      // Reset and Update Player Health.
      m_Player->LevelUpdate();
      
      // Update Player Special Items
      m_Player->UpdateSpecialItems();
      
      if(s_Level.level >= 3 && s_Level.level <=6)
        cout << "Now, Hero got the " << m_Player->SpecialItemToString() << "!\n\n";

      HelperClass::DisplayGreenLine();
        
      if (s_Level.level > 6) // For final update!
      {
        // Game Finished!
        cout << "You Won! Hero saved the village and defeated Murlocs.\n\n";
        return true;
      }

      if (s_Level.level == 6) 
      {  
        cout << "You have entered the level " << s_Level.level << " (you have to fight Murlocs)!\n"
             << "Hero's health is: " << m_Player->GetHealth() << " And, Murlocs health is: " << m_Enemy->GetHealth() << endl;
      }
      else
      {
        cout << "You have entered the level " << s_Level.level << " (you have to fight " 
             << s_Level.numberOfEnemies << " enemies)!\n" 
             << "Hero's health is: " << m_Player->GetHealth() << " And, enemies total health is: " << m_Enemy->GetHealth()<<endl;
      }  
    }

  } while (!inputValid);

  return playerDied;
}

void GameManager::SetEnemy() {
  m_Enemy.reset();
  m_Enemy = s_Level.level < 6 ? make_unique<Enemy>() : make_unique<Murlocs>();

  if(s_Level.level == 6)
      m_Enemy->SetHealth(Murlocs::murlocsHealth);
  else
    m_Enemy->SetHealth(s_Level.numberOfEnemies * m_Enemy->GetHealth());
}

void GameManager::GameLoop() {
  do {
    // Hero's turn
    cout << "\nHero, Make your move!" << '\n';
    bool playerDied = PlayerAction();
    // Hero has died. Thus, stop and break the game play!
    if (playerDied)
      break;

  } while (m_Player->GetHealth() > 0);
}