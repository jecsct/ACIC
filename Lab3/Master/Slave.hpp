
#define PED_PIN 13

namespace Slave
{
    enum Mode : int
    {
        Red = 0,
        Green = 1,
        Off = 2
    };
    int getStatus();
    void setTimerActivated();
    void initialize();
    void setState(Mode mode);
    void loop();
}