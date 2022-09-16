#include "Arduino.h"
#include "staticFunctional.h"
using staticFunctional::function; // saves typing

void hello()
{
    Serial.print("hello called at ");
    Serial.println(millis());
}

function<void(void)> f; // stores callables taking no arguments and returning void

void setup()
{
    f = hello; 
}

void loop()
{
    f();
    delay(100);
}
