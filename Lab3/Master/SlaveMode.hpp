#pragma once

class SlaveMode
{
public:
  virtual void loop() = 0;
  bool firstTime = true;

};

class SlaveModeRed : public SlaveMode
{
public:
  void loop() override;
};

class SlaveModeGreen : public SlaveMode
{
public:
  void loop() override;
};

class SlaveModeOff : public SlaveMode
{
public:
  void loop() override;
};
