#ifndef HELPERCLASS_H
#define HELPERCLASS_H

class HelperClass{
public:
  static void ClearBadBits();
  static void DisplayGreenLine();
  static int RandomRangeGenerator(int, int);
  static int RandomNumberGenerator(int);
  static int Abs(int);
  static int Clamp(int value, int min, int max);
};

#endif //HELPERCLASS_H