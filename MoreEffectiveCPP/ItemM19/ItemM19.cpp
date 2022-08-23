#include <iostream>
#include <vector>

class Number
{
public:
    Number(int num) : num_(num) { std::cout << "Number(int num)" << long(this) << std::endl; }
    Number() : num_(0) { std::cout << "Number()" << long(this) << std::endl; }
    ~Number() { std::cout << "~Number()" << long(this) << std::endl; }
    int get_num()const { return num_; }
    void set_num(int _num) { num_ = _num; }
private:
    int num_;
};

std::vector<int> return_vector1(void)
{
    std::vector<int> tmp{ 1,2,3,4,5 };
    return tmp;
}

std::vector<int>&& return_vector2(void)
{
    std::vector<int> tmp{ 1,2,3,4,5 };
    return std::move(tmp);
}

std::vector<int> return_vector3(void)
{
    std::vector<int> tmp{ 1,2,3,4,5 };
    return std::move(tmp);//   警告	C26479	请勿使用 std::move 返回局部变量。
    // 
}

std::vector<int> return_vector4(void)
{
    std::vector<int> tmp{ 1,2,3,4,5 };
    return tmp;
}

void test_return_vector()
{
    std::vector<int>&& rval_ref1 = return_vector1();
    std::vector<int>&& rval_ref2 = return_vector2();
    std::vector<int>&& rval_ref3 = return_vector3();
    std::vector<int> rval_ref4 = return_vector4();// 这种方式是最好的。利用了ROV方式，反而无需反复的构造和析构
}

void test_const_reference(const Number& num) {
    
}

void test_reference(Number& num) {

}

void test_by_value(Number num) {

}

const Number operator+(const Number& lhs, const Number& rhs)
{
    Number ret;
    ret.set_num(lhs.get_num() + rhs.get_num());
    return ret;
}

void TestMItem19()
{
    //Number n1;
    //test_const_reference(n1);
    //test_const_reference(1);
    //test_reference(1);//这个将会强制让你产生一个对象
    //test_by_value(1);
}

int main(int argn, char* argc[])
{
    // test_return_vector();
    TestMItem19();
    return 0;
}
