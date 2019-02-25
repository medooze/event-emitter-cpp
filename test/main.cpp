#include "../include/EventEmitter.h"

using namespace medooze;

class C
{
	
};

int main() 
{
    class A {};
    class B {};
    class D {};
    struct C
    {
      void onD(D &d) {
	  printf("onD\n");
      };
    };
    A a;
    B b;
    C c;
    D d;
    EventEmitter emitter;

    [&](){
	auto lambda = [](A &a){
		printf("A\n");
	};
	emitter
	    .on<A>(lambda)
	    .on<B>([](B &b){
		printf("B\n");
	    })
	    .on<D>(std::bind(&C::onD, &c, std::placeholders::_1));
    }();

    emitter.emit(a);
    emitter.emit(b);
    emitter.emit(d);
}
