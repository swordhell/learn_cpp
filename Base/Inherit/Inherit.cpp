#include <iostream>
#include <assert.h>

using namespace std;

#pragma pack(push,1)
class A
{
public:
	A() { a = 0; }
	int a;
	char buff[100]; // 我们将A中填充一些内存块，将会看到使用非虚拟继承的类，将会膨胀的很厉害。
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
	A a; // {_vptr$A = 0x4020a0 <vtable for A+16>, a = 0}
	// 多态是使用 virtual function table + virtual pointer

	B b; // {_vptr$A = 0x4020d0 <vtable for B+16>, a = 2}, b = 2}
	C c; // {_vptr$A = 0x402108 <vtable for C+16>, a = 3}, c = 3}
	D d; // {<B> = {<A> = {_vptr$A = 0x402140 <vtable for D+16>, a = 2}, b = 2}, <C> = {<A> = {_vptr$A = 0x402158 <vtable for D+40>, a = 3}, c = 3}, <No data fields>}
	std::cout << "a " << sizeof(a) << std::endl;//12 = 虚表指针：_vptr$A 8 byte + int(4)
	std::cout << "b " << sizeof(b) << std::endl;//16 = 虚表指针：_vptr$A 8 byte + A::a int(4) + B::b int(4) 
	std::cout << "c " << sizeof(c) << std::endl;//16 = 虚表指针：_vptr$A 8 byte + A::a int(4) + C::c int(4) 
	std::cout << "d " << sizeof(d) << std::endl;//32 = 虚表指针：_vptr$A 8 byte + B::A::a int(4) + B::b int(4) + _vptr$A 8 byte + C::A::a int(4) + C::c int(4)
	// b和c拥有独立的A对象，互相不共享，意味着，如果想在d层级调用A变量需要指定基类。
	d.fun();

	//std::cout << "d.a" << d.a << std::endl;// 这样会有问题
	std::cout << "d.B::a" << d.B::a << std::endl;// 他们是分离的
	std::cout << "d.C::a" << d.C::a << std::endl;
	std::cout << std::endl;

	// virtual inherit 代表共享使用相同的A
	B1 b1; // {<A> = {_vptr$A = 0x4021d8 <vtable for B1+56>, a = 22}, _vptr$B1 = 0x4021b8 <vtable for B1+24>, b = 22}
	C1 c1; // {<A> = {_vptr$A = 0x402258 <vtable for C1+56>, a = 33}, _vptr$C1 = 0x402238 <vtable for C1+24>, c = 33}
	D1 d1; // {<B1> = {<A> = {_vptr$A = 0x4022f8 <vtable for D1+88>, a = 33}, _vptr$B1 = 0x4022b8 <vtable for D1+24>, b = 22}, <C1> = {_vptr$C1 = 0x4022d8 <vtable for D1+56>, c = 33}, <No data fields>}
	std::cout << "b1 " << sizeof(b1) << std::endl;// 24 = 虚表指针：_vptr$A 8 byte + a int(4) + _vptr$B1 8 byte + b int(4)
	std::cout << "c1 " << sizeof(c1) << std::endl;// 24 = 虚表指针：_vptr$A 8 byte + a int(4) + _vptr$C1 8 byte + c int(4)
	std::cout << "d1 " << sizeof(d1) << std::endl;// 36 = 虚表指针：_vptr$A 8 byte + a int(4) + _vptr$B1 8 byte + b int(4) + _vptr$C1 8 byte + c int(4)

	std::cout << "d1.B1::a " << d1.B1::a << std::endl; // 这两个值都会相同
	std::cout << "d1.C1::a " << d1.C1::a << std::endl;
	std::cout << std::endl;

	return 0;
}
