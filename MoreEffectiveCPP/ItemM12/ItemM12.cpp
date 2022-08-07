// g++ -std=c++17 -g -fsanitize=address ItemM12.cpp -o ../bin/ItemM12
#include <iostream>

class Widget {
public:
  Widget(const Widget& o) : widgetSize_(o.widgetSize_) {std::cout << "Widget(const Widget& o)" << std::endl;}
  Widget(int widgetSize) : widgetSize_(widgetSize) {std::cout << "Widget(int widgetSize)" << std::endl;}
  ~Widget() { std::cout << "~Widget()..." << std::endl; }
  int widgetSize_;
};

class SpecialWidget : public Widget {
public:
  SpecialWidget() : Widget(10), specialWidgetSize_(8) {std::cout << "SpecialWidget()..." << std::endl;}
  ~SpecialWidget() { std::cout << "~SpecialWidget()..." << std::endl; }
  int specialWidgetSize_;
};

void WillThrow() {
    SpecialWidget localSpecialWidget;
    Widget& rw = localSpecialWidget;
    if (localSpecialWidget.specialWidgetSize_ == 8) {
        throw rw;
    }
}

void Catch2() {
    try {
        WillThrow();
    } catch (Widget& w) {
        std::cout << "Caught Widget" << w.widgetSize_<< std::endl;
        throw w;
    }
}

int main(int argn, char *argc[]) {
    try {
        Catch2();
    } catch (Widget& w) {
        std::cout << "Caught Widget" << w.widgetSize_<< std::endl;
    }
  return 0;
}
