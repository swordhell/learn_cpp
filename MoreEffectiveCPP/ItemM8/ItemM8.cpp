// g++ -std=c++17 -g -fsanitize=address ItemM8.cpp -o ../bin/ItemM8
#include <iostream>

class Widget {
public:
  Widget(int widgetSize) : widgetSize_(widgetSize) {}
  ~Widget() { std::cout << "~Widget()..." << std::endl; }
  int widgetSize_;
};

Widget *constructWidgetInBuffer(void *buffer, int widgetSize) {
  return new (buffer) Widget(widgetSize);
}

int main(int argn, char *argc[]) {
  int widgetSize = 10;
  char *buffer = new char[sizeof(Widget)];
  Widget *pw = constructWidgetInBuffer(buffer, widgetSize);
  std::cout << pw->widgetSize_ << std::endl;
  // delete pw; // 这种写法是存在问题的
  pw->~Widget();
  delete []buffer;
  return 0;
}
