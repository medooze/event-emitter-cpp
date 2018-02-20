# EventEmitter-cpp
C++ header only event emitter

# Usage

Just include the EventEmitter header

```
#include "EventEmitter.h"

medooze::EventEmitter emitter

```

# API

## on<T>(T event)

Add a callback when the T type event is emitter. Note: only one handler per type currently supported

## emmit(T event)

Call the event handler associated to a givent type


# Example

```
#include "EventEmitter.h"

using namespace medooze;

class A {};
class B {};

int main() 
{
    EventEmitter emitter;

    emitter
        .on<A>([](A &a){
            printf("A");
        })
        .on<B>([](B &b){
            printf("B");
        });

    A a;
    B b;

    emitter.emit(a);
    emitter.emit(b);
    
}
```