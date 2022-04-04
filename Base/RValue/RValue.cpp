#include <iostream>

// 《深入应用C++11：代码优化与工程级应用》
// https://github.com/qicosmos/cosmos


#include <iostream>
#include <string>
#include <typeinfo>
#include <memory>
#include <cstdlib>
#include <vector>
#ifndef _MSC_VER
#include <cxxabi.h>
#endif

template <class T>
std::string type_name()
{
	typedef typename std::remove_reference<T>::type TR;
	std::unique_ptr<char, void(*)(void*)> own(
#ifndef __GNUC__
		nullptr,
#else
		abi::__cxa_demangle(typeid(TR).name()), nullptr,
		nullptr, nullptr),
#endif
		std::free);

		std::string r = own != nullptr ? own.get() : typeid(TR).name();

		if (std::is_const<TR>::value)
		{
			r += " const";
		}
		if (std::is_volatile<TR>::value)
		{
			r += " volatile";
		}

		if (std::is_lvalue_reference<T>::value)
		{
			r += "&";
		}
		else if (std::is_rvalue_reference<T>::value)
		{
			r += "&&";
		}

		return r;
}

template <typename T>
void Func(T&& t)
{
	std::cout << type_name<T>() << std::endl;
}

void TestValueType() {

	std::string str = "Test";
	Func(str);
	Func(std::move(str));

	system("pause");
}

void TestA();
void TestMyString();

int main(int argn,char* argc[]) {
	//TestA();
	TestMyString();
	return 0;
}
