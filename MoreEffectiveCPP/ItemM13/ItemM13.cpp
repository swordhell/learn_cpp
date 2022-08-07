// g++ -std=c++17 -g -fsanitize=address ItemM13.cpp -o ../bin/ItemM13
#include <iostream>
#include <exception>

void someFunction() {
	static std::exception ex("my exception");
	throw& ex;
}

void someFunction2() {
	std::exception* pex = new std::exception("exception 2");
	throw pex;
}

void someFunction3() {
	throw std::exception("exception 3");
}

void doSomething() {
	try
	{
		someFunction2();
	}
	catch (std::exception* ex)
	{
		std::cout << ex->what() << std::endl;
		delete ex;
	}
}

int main(int argn, char* argc[]) {
	doSomething();
	return 0;
}
