// 变参模板
// https://www.stroustrup.com/hopl20main-p5-p-bfc9cd4--final.pdf 4.3.2
// 参考书《https://github.com/Walton1128/CPP-Templates-2nd--》第四章
#include <iostream>
#include <stdexcept>

template<typename T,typename... Args>
void printf(const char* s, const T& value, const Args&... args)
{
	while (*s)
	{
		if (*s == '%' && *++s != '%')
		{
			std::cout << value;
			printf(++s, args...);
		}
		std::cout << *s++;
	}
	throw std::runtime_error("extra arguments provided to printf");
}

void first_test()
{

	try
	{
		const char* msg = "The value of %s is about %g (unless you live in %s).\n";
		printf(msg, std::string("pi"), 3.14159, "Indiana");
	}
	catch (const std::exception& e)
	{
		std::cout << e.what();
	}
}

int main(int argn,char* argc[]) {
	return 0;
}
