#include <string>
#include <iterator>
#include <iostream>
#include <algorithm>
#include <vector>

int main(int argn, char* argc[]) {
	std::vector<int> v = { 0,1,2,3,4,5,6,7 };
	auto outputfun = [](const int& param) {std::cout << param << ","; };

	v.erase(v.begin());
	std::for_each(v.cbegin(), v.cend(), outputfun);
	std::cout << std::endl;

	auto it = std::next(v.begin(), 4);
	v.emplace(it, 88);
	std::for_each(v.cbegin(), v.cend(), outputfun);
	std::cout << std::endl;

	return 0;
}
