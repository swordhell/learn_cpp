// g++ -std=c++17 -g -fsanitize=address ItemM6.cpp -o ../bin/ItemM6
#include <iostream>
class UPInt { // "unlimited precision int"
public:
  UPInt(int i) : i_(i) {}
  //   UPInt &operator++();         // ++ 前缀
  //   const UPInt operator++(int); // ++ 后缀
  //   UPInt &operator+=(int);      // += 操作符，UPInts
  //                                // 与 ints 相运算
  //   UPInt &operator--();         // -- 前缀
  //   const UPInt operator--(int); // -- 后缀

  // 前缀形式：增加然后取回值
  UPInt &operator++() {
    *this = *(this + 1); // 增加
    return *this;        // 取回值
  }
  // postfix form: fetch and increment
  const UPInt operator++(int) {
    UPInt oldValue = *this; // 取回值
    ++(*this);              // 增加
    return oldValue;        // 返回被取回的值
  }
  int i_;
};
int main(int argn, char *argc[]) {
  UPInt i[3] = {
	UPInt(0),
	UPInt(1),
	UPInt(2)
  };
  UPInt& it = i[0];
  ++it; // 调用 i.operator++();
  std::cout << it.i_ << std::endl;
  it++; // 调用 i.operator++(0);
  std::cout << it.i_ << std::endl;
  return 0;
}
