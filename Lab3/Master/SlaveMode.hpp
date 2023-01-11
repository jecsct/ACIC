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
    bool firstTime = true;
};

class SlaveModeGreen : public SlaveMode
{
public: 
  void loop() override;
private:
    bool firstTime = true;
};

class SlaveModeOff : public SlaveMode
{
public: 
  void loop() override;

};
