#include <iostream>
#include <string>
#include <stdint.h>
#include <tuple>
#include <iostream>

auto get_name_age() -> std::tuple<std::string,uint8_t>{
  return std::make_tuple("小明", 16);
}

int main() {
  auto t = get_name_age();
  auto name = std::get<0>(t);
  auto age = std::get<1>(t);
  std::cout << "name: " << name << " age: " << int(age) << std::endl;
  std::string name1;
  uint8_t age1;
  std::tie(name1,age1)=t;
  std::cout <<"name1: " << name << " age1: " << int(age1) << std::endl;
  return 0;
}
