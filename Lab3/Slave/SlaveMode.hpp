#pragma once

// Warning: This is a code example for the article "guideline for modular firmware".
//          It is code in a transition phase, do not use it as it is!


class SlaveMode
{
public:
  virtual void loop() = 0;
};

class SlaveModeRed : public SlaveMode
{
public: // Implement AnimationMode
  void loop() override;
};

class SlaveModeGreen : public SlaveMode
{
public: // Implement AnimationMode
  void loop() override;
private:
    bool _firstTime = false;
};

class SlaveModeOff : public SlaveMode
{
public: // Implement AnimationMode
  void loop() override;
private:
    bool _firstTime = false;
};
