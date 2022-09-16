#include "Arduino.h"
#include "staticFunctional.h"
using staticFunctional::function; // saves typing

function<void(void)> f;       // stores callables taking no arguments and returning void
function<int(void)> g;        // stores callables taking no arguments and returning int
function<double(uint32_t)> h; // stores callables taking a uint32_t argument and returning double

void setup()
{
    f = [] { Serial.println("Simple lambda"); };

    g = [] {
        Serial.println("Lambda returning int value");
        return millis();
    };

    h = [](uint32_t i) {
        Serial.print("Lambda accepting int, returning double. Got i =");
        Serial.println(i);
        return 3.1415 * i;
    };
}

void loop()
{
    Serial.println("-----------------------------------------------");

    f();
    Serial.println();

    int i    = g();
    Serial.printf("i=%d\n\n", i);

    double x = h(millis());
    Serial.printf("x=%f\n", x);

    delay(500);
}