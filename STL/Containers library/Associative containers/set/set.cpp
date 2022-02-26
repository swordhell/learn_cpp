#include <set>
#include <unordered_set>
#include <iostream>
#include <string>

int main(int argn, char* argc[]) {
	std::set<std::string> unique_cites = {"Braunschweig", "Hanover", "Frankfurt", "Paris", "Paris"};
	std::multiset<std::string> cities = { "Braunschweig", "Hanover", "Frankfurt", "Paris", "Frankurt"};
	std::unordered_set<std::string> unordered_unique_cites = { "Braunschweig", "Hanover", "Frankfurt", "Paris", "Paris" };
	std::unordered_multiset<std::string> unordered_cites = { "Braunschweig", "Hanover", "Frankfurt", "Paris", "Paris" };

	for (const auto& elem : unique_cites)
	{
		std::cout << elem << " ";
	}
	std::cout << std::endl;

	for (const auto& elem : cities)
	{
		std::cout << elem << " ";
	}
	std::cout << std::endl;

	cities.insert({ "London", "Munich", "Hanover", "Braunschweig" });
	for (const auto& elem : cities)
	{
		std::cout << elem << " ";
	}
	std::cout << std::endl;
	return 0;
}
