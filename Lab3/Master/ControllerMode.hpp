#pragma once

// Warning: This is a code example for the article "guideline for modular firmware".
//          It is code in a transition phase, do not use it as it is!

#include <Arduino.h>

class ControllerMode
{
public:
  virtual void loop() = 0;
};

class ControllerModeOn : public ControllerMode
{
public: // Implement AnimationMode
  void loop() override;
};

class ControllerModeOff : public ControllerMode
{
public: // Implement AnimationMode
  void loop() override;
private:
    bool _firstTime = false;
};
