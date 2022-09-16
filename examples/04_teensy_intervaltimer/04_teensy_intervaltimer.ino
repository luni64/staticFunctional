/***************************************************************
 * This example demonstrates the use of staticFunctional
 * in real life applications.
 * It modifies the Teensyduino IntervalTimer code to accept
 * staticFunctional::function callbacks 
 ***************************************************************/

#include "IntervalTimerTest.h"

IntervalTimerTest timer[4];

void onTimer(int ch)
{
    Serial.printf("onTimer (channel:%d)\n", ch);
}

void setup()
{
    // capturing lambda
    for (int i = 0; i < 4; i++)
    {
        timer[i].begin([i] { onTimer(i); }, 50'000*(i+1));
    }
}

void loop()
{
}