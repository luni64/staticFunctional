#include "Arduino.h"
#include "staticFunctional.h"

// Simple example showing how to use the function class to store callback functions
// in a user class.
// The clock invokes the callback at the time (ms since reset) passed into setAlarm.
// The callback can be any void(uint32) callable. I.e.  void somefunction(uint32),
// some corresponding lambda expression...

class Clock
{
    using callback_t = staticFunctional::function<void(uint32_t)>;

 public:
    void setAlarm(uint32_t ms, callback_t cb)
    {
        t_alarm  = ms;
        callback = cb;
        running  = true;
    }

    void tick()
    {
        if (!running) return;

        if (millis() >= t_alarm)
        {
            callback(millis());
            running = false;
        }
    }

 protected:
    bool running;
    uint32_t t_alarm = 0;
    callback_t callback;
};

Clock myClock;

void setup()
{
    myClock.setAlarm(4321, [](uint32_t t) { Serial.printf("Alarm called at t=%d\n", t); });
}

void loop()
{
    myClock.tick();
}