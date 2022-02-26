#include <deque>
#include <algorithm>
#include <iostream>

int main(int argn, char* argc[]) {
	std::deque<int> d = { 0,1,2,3,4,5,6,7 };
	auto outputfun = [](const int& param) {std::cout << param << ","; };

	d.erase(d.begin());
	std::for_each(d.cbegin(), d.cend(), outputfun);
	std::cout << std::endl;

	auto it = std::next(d.begin(), 4);
	d.emplace(it, 88);
	std::for_each(d.cbegin(), d.cend(), outputfun);
	std::cout << std::endl;

	return 0;
}
