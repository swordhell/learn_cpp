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
		std::cout << "copy_data(const char* s) is called!" << std::endl;
	}

public:
	MyString()
	{
		m_data = NULL;
		m_len = 0;
		std::cout << "MyString() Constructor is called!" << std::endl;
	}

	MyString(const char* p)
	{
		m_len = strlen(p);
		copy_data(p);
		std::cout << "MyString(const char* p) Constructor is called!" << std::endl;
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

	//MyString(MyString&& str)noexcept
	//{
	//	m_len = str.m_len;
	//	m_data = str.m_data;
	//	str.m_len = 0;
	//	str.m_data = nullptr;
	//	std::cout << "RValue Copy Constructor is called! source:" << m_data << std::endl;
	//}

	//MyString& operator=(MyString&& str)noexcept
	//{
	//	if (this != &str)
	//	{
	//		if (m_data != nullptr)
	//		{
	//			delete[] m_data;
	//		}
	//		m_len = str.m_len;
	//		m_data = str.m_data;
	//		str.m_len = 0;
	//		str.m_data = nullptr;
	//	}
	//	std::cout << "RValue Copy Assignment is called! source:" << m_data << std::endl;
	//	return *this;
	//}

	virtual ~MyString()
	{
		if (m_data != NULL)
		{
			delete[] m_data;
		}
		std::cout << "Destructor is called!" << std::endl;
	}
};

void TestMyString() {

	MyString a;
	a = MyString("Hello"); // 由于这个里面是个将亡值，可以被解释成为右值引用，所以可以让这个过程中减少一次内存拷贝。
	// 对比的话，就可以注释掉
	// MyString& operator=(MyString&& str)noexcept
	// MyString& operator=(const MyString& str)
	

	// 有右值引用的情况下：
	// MyString() Constructor is called!
	// copy_data(const char* s) is called!
	// MyString(const char* p) Constructor is called!
	// RValue Copy Assignment is called!source:Hello
	// Destructor is called!
	// copy_data(const char* s) is called!
	// MyString(const char* p) Constructor is called!
	// RValue Copy Constructor is called!source : World
	// Destructor is called!

	// 无右值引用的情况下：
	//MyString() Constructor is called!
	//	copy_data(const char* s) is called!
	//	MyString(const char* p) Constructor is called!
	//	copy_data(const char* s) is called!
	//	Copy Assignment is called!source:Hello
	//	Destructor is called!
	//	copy_data(const char* s) is called!
	//	MyString(const char* p) Constructor is called!
	//	copy_data(const char* s) is called!
	//	Copy Constructor is called!source : World
	//	Destructor is called!
	std::vector<MyString> vec;
	vec.push_back(MyString("World"));

	system("pause");
}

int g_constructCount = 0;
int g_destructCount = 0;
struct A
{
	A()
	{
		std::cout << "construct: " << ++g_constructCount << std::endl;
	}
	A(const A& a)
	{
		std::cout << "copy construct: " << ++g_constructCount << std::endl;
	}
	~A()
	{
		std::cout << "destruct: " << ++g_destructCount << std::endl;
	}
};

A GetA()
{
	return A();
}

void TestA()
{
	A&& a = GetA();
	return;
}

