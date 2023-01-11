#pragma once

// Warning: This is a code example for the article "guideline for modular firmware".
//          It is code in a transition phase, do not use it as it is!

#include <Arduino.h>

class ControllerMode
{
public:
  virtual void loop(int *entries, int numEntries) = 0;

};

class ControllerModeOn : public ControllerMode
{
public: // Implement AnimationMode
  void loop(int *entries, int numEntries) override;
private:
  int change_timer = 0;
  int entry_timer = 0;
  bool first_time = 0;
  int currentGreenEntrySemaphore = 0;
};

class ControllerModeOff : public ControllerMode
{
public: // Implement AnimationMode
  void loop(int *entries, int numEntries) override;
private:
    bool _firstTime = false;
};
