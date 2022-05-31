#include <ctime>
#include <iostream>
#include <sstream>
#include <iomanip>

std::time_t str2time_t(std::string&& str) {
	struct std::tm tm;
	std::istringstream ss(str);
	ss >> std::get_time(&tm, "%Y-%m-%d %H:%M:%S");
	return mktime(&tm);
}

std::string sec2str(double sec) {
	std::time_t seconds(sec); // you have to convert your input_seconds into time_t
	std::tm* p = std::gmtime(&seconds); // convert to broken down time

	std::ostringstream os;
	os << " days = " << p->tm_yday;
		os << " hours = " << p->tm_hour;
	os << " minutes = " << p->tm_min ;
	os << " seconds = " << p->tm_sec ;
	return os.str();
}

int main(int argn, char* argc[]) {
	auto start = str2time_t("2022-03-17 00:00:00");
	auto end = str2time_t("2022-06-01 00:00:00");
	auto sec = std::difftime(end, start);
	std::cout << sec2str(sec);
	return 0;
}