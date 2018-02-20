#include "../include/EventEmitter.h"

using namespace medooze;

int main() 
{
    class A {};
    class B {};
    A a;
    B b;
    EventEmitter emitter;

    [&](){
	auto lambda = [](A &a){
		printf("A");
	};
	emitter
	    .on<A>(lambda)
	    .on<B>([](B &b){
		printf("B");
	    });
    }();

    emitter.emit(a);
    emitter.emit(b);
    
}