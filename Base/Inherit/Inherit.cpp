#include <iostream>

using namespace std;

#pragma pack(push,1)
class A
{
public:
	A() { a = 0; }
	int a;
	virtual void fun() { std::cout << "A::fun()\n"; };
};

class B : public A
{
public:
	B() { a = 2; b = 2; }
	int b;
	virtual void fun() { std::cout << "B::fun()\n"; };
};

class C : public A
{
public:
	C() { a = 3; c = 3; }
	int c;
	virtual void fun() { std::cout << "C::fun()\n"; };
};

class D: public B,public C
{
public:
	virtual void fun() { std::cout << "D::fun()\n"; };
};

class B1 : virtual public A
{
public:
	B1() { a = 22; b = 22; }
	int b;
	virtual void fun() { std::cout << "b1::fun()\n"; };
};

class C1 : virtual public A
{
public:
	C1() { a = 33; c = 33; }
	int c;
	virtual void fun() { std::cout << "c1::fun()\n"; };
};

class D1 : public B1, public C1
{
public:
	virtual void fun() { std::cout << "D::fun()\n"; };
};
template <class type, int dim>
class Point
{
public:
	Point() = default;
	Point(type coords[dim]) {
		for (int index = 0; index < dim; index++)
			_coords[index] = coords[index];
	}
	type& operator[](int index) {
		assert(index < dim&& index >= 0);
		return _coords[index];
	}
	type operator[](int index) const {
		assert(index < dim&& index >= 0);
		return _coords[index];
	}
private:
	type _coords[dim];
};
#pragma pack(pop)

template<class type,int dim>
ostream&
operator << (ostream& os, const Point<type, dim>& pt)
{
	os << "(";
	for (int ix = 0; ix < dim - 1; ix++)
		os << pt[ix] << ", ";
	os << pt[dim - 1];
	os << " )";
	return os;
}

int main(int argn, char* argc[]) {
	std::cout << "Hello the world!" << std::endl;
	A a;
	B b;
	C c;
	D d;
	B1 b1;
	C1 c1;
	D1 d1;

	std::cout << "a " << sizeof(a) << std::endl;//12 int(4) + vfptr 8 byte
	std::cout << "b " << sizeof(b) << std::endl;//16 = 一个完整的A 12 + int(4) 
	std::cout << "c " << sizeof(c) << std::endl;// 16 = 一个完整的A 12 + int(4) 
	std::cout << "d " << sizeof(d) << std::endl;//32 = 
	std::cout << std::endl;

	std::cout << "b1 " << sizeof(b1) << std::endl;// 24
	std::cout << "c1 " << sizeof(c1) << std::endl;// 24
	std::cout << "d1 " << sizeof(d1) << std::endl;// 36
	std::cout << std::endl;

	
	return 0;
}
