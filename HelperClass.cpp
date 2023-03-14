#include "HelperClass.h"
#include <iomanip>
#include <iostream>
#include <limits>
using namespace std;

void HelperClass::DisplayGreenLine() {
  cout << "\033[32m" << '+' << setfill('+') << setw(111) << right << '+'
       << "\033[0m" << endl
       << endl;
}

void HelperClass::ClearBadBits() {
  if (cin.fail()) {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
  }
}

int HelperClass::RandomRangeGenerator(int min, int max) {
  int randomNumber;
  randomNumber = (rand() % (max + 1 - min) + min);
  return randomNumber;
}

int HelperClass::RandomNumberGenerator(int x) {
  int randomNumber;
  randomNumber = rand() % x;
  return randomNumber;
}

int HelperClass::Abs(int val) { return val < 0 ? val * -1 : val; }

int HelperClass::Clamp(int value, int min, int max)
{
  if(value < min) value = min;
  else if(value > max) value = max;

  return value;
}