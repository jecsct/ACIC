#pragma once


class SlaveMode
{
public:
  virtual void loop() = 0;
};

class SlaveModeRed : public SlaveMode
{
public: 
  void loop() override;
private:
    bool firstTime = false;
};

class SlaveModeGreen : public SlaveMode
{
public: 
  void loop() override;
private:
    bool firstTime = false;
};

class SlaveModeOff : public SlaveMode
{
public: 
  void loop() override;

};
