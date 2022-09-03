#include <thread>
#include <iostream>
#include <vector>
#include <memory>
#include <chrono>

std::vector<std::thread> g_list;
std::vector<std::shared_ptr<std::thread>> g_list2;

void f1(int n)
{
    for (int i = 0; i < 5; ++i) {
        std::cout << "Thread " << n << " executing\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}

void f2(int& n)
{
    for (int i = 0; i < 5; ++i) {
        std::cout << "Thread 2 executing\n";
        ++n;
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}

void BaseUse()
{
    int n = 0;
    std::thread t1; // t1 is not a thread
    std::thread t2(f1, n + 1); // pass by value
    std::thread t3(f2, std::ref(n)); // pass by reference
    std::thread t4(std::move(t3)); // t4 is now running f2(). t3 is no longer a thread

    std::cout << t1.get_id() << std::endl; // 获取当前线程ID
    std::cout << std::thread::hardware_concurrency() << std::endl; // 获取硬件CPU个数

    t2.join();
    t4.join();
    std::cout << "Final value of n is " << n << '\n';
}

void func()
{
}

void CreateThread()
{
    std::thread t(func);
    g_list.push_back(std::move(t)); //直接利用右值引用复用这块内存
    g_list2.push_back(std::make_shared<std::thread>(func));
}

void TestLifeTime()
{
    CreateThread();
    for (auto& thread : g_list)
    {
        thread.join();
    }
    for (auto& thread : g_list2)
    {
        thread->join();
    }
}

int main()
{
    BaseUse();
    TestLifeTime();
}
