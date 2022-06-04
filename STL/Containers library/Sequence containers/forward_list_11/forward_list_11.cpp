#include <forward_list>
#include <iostream>
#include <algorithm>

int main(int argn, char* argc[]) {
	std::forward_list<int> forward = { 0,1,2,3,4,5,6,7 };
	auto it = std::next(forward.begin(),4);
	forward.erase_after(it);
	forward.erase_after(forward.before_begin());
	std::for_each(forward.cbegin(), forward.cend(), [](const int& param) {
		std::cout << param << ",";
		});
	std::cout << std::endl;
	forward.emplace_after(it, 88);
	std::for_each(forward.cbegin(), forward.cend(), [](const int& param) {
		std::cout << param << ",";
		});
	std::cout << forward.empty()
		<< forward.max_size();
	std::cout << std::endl;
	return 0;
}
