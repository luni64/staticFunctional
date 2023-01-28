[![PlatformIO Registry](https://badges.registry.platformio.org/packages/luni64/library/staticFunctional.svg)](https://registry.platformio.org/libraries/luni64/staticFunctional)
[![arduino-library-badge](https://www.ardu-badge.com/badge/staticFunctional.svg?)](https://www.ardu-badge.com/staticFunctional)

# staticFunctional

## Purpose
The library provides a drop in replacement for std::function 

Key features:
- Arduino framework compatible
- Small memory overhead (e.g. for a Teensy 3.2 board it reduces code size by ~10kB and uses ~1kB less static memory).
- No dynamic memory allocation
- Compatible to C++11 (or higher) GCC toolchains (does not work with gcc-avr)

It can be used to provide easy to use callback APIs for system and user classes.

## Usage

Below a simple usage example showing how to use the static function class to call free functions, non static member functions, lambda expressions and functors.
```c++
#include "staticFunctional.h"
using namespace staticFunctional; // save typing

class MyClass
{
 public:
    void nonStaticMemberFunction() {
        Serial.printf("nonStaticMemberFunction i=%d\n", i);
    }

    void operator()() const {
        Serial.printf("functor 2i=%d\n", 2*i);
    }
    int i = 42;
};
MyClass myClass;

void freeFunc(){
    Serial.println("free function");
}

void setup()
{
    while (!Serial) {}

    function<void(void)> f; // function taking no arguments and returning nothing

    f = freeFunc;
    f();

    f = [] { Serial.println("lambda expression"); };
    f();

    f = [] { myClass.nonStaticMemberFunction(); }; // non static member function
    f();

    f = myClass; // functor, f uses operator ()()
    f();
}

void loop(){
}

// prints:
// free function
// lambda expression
// nonStaticMemberFunction i=42
// functor 2i=84
```

The examples folder contains more usage examples and a reworked **Teensy IntervalTimer** class which extends the API to accept more or less anything which can be called (functions, member functions, lambdas, functors..) as callback. The required revision of the IntervalTimer was mainly to adapt the declaration of the `begin(...)` functions and the static array `funct_table`. I.e. `begin(void(*func)(),...)` became `begin(callback_t funct,...)`.


## Credits

The library is based on code from this [forum post](https://www.c-plusplus.net/forum/topic/344451/std-function-und-std-bind-durch-einfachere-eigene-variante-ersetzen-signal-slot/17) on the [c++ Community forum](https://www.c-plusplus.net/forum/) (Author [@Arcoth](https://github.com/Arcoth))


