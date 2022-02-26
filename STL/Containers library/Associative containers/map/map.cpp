#include <map>
#include <unordered_map>
#include <iostream>
#include <string>

int main(int argn, char* argc[]) {
	std::map<int, std::string> unique_map = { {1,"Abel"},{1,"Franky"}, {2,"Sean"} };
	std::multimap<int,std::string> multi_map = { {1,"Abel"},{1,"Franky"}, {2,"Sean"} };

	for (const auto& elem : unique_map)
	{
		std::cout << elem.first << "=" << elem.second << " ";
	}
	std::cout << std::endl;

	for (const auto& elem : multi_map)
	{
		std::cout << elem.first << "=" << elem.second << " ";
	}
	std::cout << std::endl;
	return 0;
}
