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

class MyString
{
private:
	char* m_data;
	size_t m_len;
	void copy_data(const char* s)
	{
		m_data = new char[m_len + 1];
		memcpy(m_data, s, m_len);
		m_data[m_len] = '\0';
	}

public:
	MyString()
	{
		m_data = NULL;
		m_len = 0;
	}

	MyString(const char* p)
	{
		m_len = strlen(p);
		copy_data(p);
	}

	MyString(const MyString& str)
	{
		m_len = str.m_len;
		copy_data(str.m_data);
		std::cout << "Copy Constructor is called! source:" << str.m_data << std::endl;
	}

	MyString& operator=(const MyString& str)
	{
		if (this != &str)
		{
			m_len = str.m_len;
			copy_data(str.m_data);
		}
		std::cout << "Copy Assignment is called! source:" << str.m_data << std::endl;
		return *this;
	}

	virtual ~MyString()
	{
		if (m_data != NULL)
		{
			delete[] m_data;
		}
	}
};

void TestMyString() {

	MyString a;
	a = MyString("Hello");

	std::vector<MyString> vec;
	vec.push_back(MyString("World"));

	system("pause");
}

int main(int argn,char* argc[]) {
	return 0;
}
