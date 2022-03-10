#include <iostream>

#pragma pack(push,1)
class A
{
public:
	int a;
};

class B : public A
{
public:
	int b;
};

class C : public A
{
public:
	int c;
};

class D: public B,public C
{
public:
};

#pragma pack(pop)

int main(int argn, char* argc[]) {
	std::cout << "Hello the world!" << std::endl;
	A a;
	B b;
	C c;
	D d;
	std::cout << sizeof(a) << std::endl;//4 int(4)
	std::cout << sizeof(b) << std::endl;//16 int(4)+int(4)+ptr(8)
	std::cout << sizeof(c) << std::endl;//16 int(4)+int(4)+ptr(8)
	std::cout << sizeof(d) << std::endl;//28 int(4)+int(4)+int(4)+ptr(8)+ptr(8)
	return 0;
}
