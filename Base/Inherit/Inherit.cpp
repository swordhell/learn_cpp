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

class B1 : virtual public A
{
public:
	int b;
};

class C1 : virtual public A
{
public:
	int c;
};

class D1 : public B1, public C1
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
	B1 b1;
	C1 c1;
	D1 d1;

	std::cout << "a " << sizeof(a) << std::endl;//4 int(4)
	std::cout << "b " << sizeof(b) << std::endl;//8
	std::cout << "c " << sizeof(c) << std::endl;//8
	std::cout << "d " << sizeof(d) << std::endl;//16
	std::cout << std::endl;
	std::cout << "b1 " << sizeof(b1) << std::endl;//16
	std::cout << "c1 " << sizeof(c1) << std::endl;//16
	std::cout << "d1 " << sizeof(d1) << std::endl;//28
	return 0;
}
