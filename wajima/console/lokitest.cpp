#include <iostream>
#include <pss/std/SmartPtr.hpp>

class A {
public:
	A(){
	}
};

typedef ::Loki::SmartPtrDef<A, ::pss::std::RefCounted >::type SmartPtr;

int main(int argc, char *argv[]) {
	SmartPtr a = SmartPtr(new A());
	return 0;
}