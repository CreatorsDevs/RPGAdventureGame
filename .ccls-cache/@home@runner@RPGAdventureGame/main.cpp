#include "GameManager.h"
#include "HelperClass.h"
#include "Player.h"
#include <iostream>
using namespace std;

int main() {
  srand(time(0));
  GameManager &gameManager = GameManager::GetInstance();
  gameManager.GameTitle();
  gameManager.Instructions();
  HelperClass::DisplayGreenLine();
  gameManager.Update();
  
  return 0;
}