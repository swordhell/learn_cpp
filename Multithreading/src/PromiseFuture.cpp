#include <iostream>
#include <future>
#include <utility>
#include <thread>
#include <vector>

void test_promise()
{
	std::promise<int> pr;
	std::thread t([](std::promise<int>& p) {
			p.set_value_at_thread_exit(9);
		},
		std::ref(pr));
	std::future<int> f = pr.get_future();
	auto r = f.get();
}

void test_future_status()
{
	std::future_status status;
	std::future<int> fu;
		do {
			status = fu.wait_for(std::chrono::seconds(1));
			if (status == std::future_status::deferred) {
				std::cout << "deferred\n";
			}
			else if (status == std::future_status::timeout) {
				std::cout << "timeout!\n";
			}
			else if (status == std::future_status::ready) {
				std::cout << "ready!\n";
			}
		} while (status != std::future_status::ready);
}

int func(int x) { return x + 2; }

void test_task()
{
	std::packaged_task<int(int)> tsk(func);
	std::future<int> fut = tsk.get_future();

	std::thread(std::move(tsk), 2).detach();

	int value = fut.get();
	std::cout << "The result is " << value << std::endl;

	std::vector<std::shared_future<int>> v;
	auto f = std::async(std::launch::async, [](int a, int b) {
		return a + b; }, 2, 3);
	v.push_back(f);

	std::cout << "The shared_future result is " << v[0].get() << std::endl;
}

void test_async()
{
	std::future<int> f1 = std::async(std::launch::async, []() {
		return 8;
		});
	std::cout << f1.get() << std::endl;
	std::future<int> f2 = std::async(std::launch::async, []() {
		std::cout << 8 << endl;
		});
	f2.wait();
	std::future<int> f3 = std::async(std::launch::async, []() {
		std::this_thread::sleep_for(std::chrono::seconds(3));
		return 8;
		});

	std::cout << "waiting ... \n";
	std::future_status status;
	do {
		status = f3.wait_for(std::chrono::seconds(1));
		if (status == std::future_status::deferred) {
			std::cout << "deferred\n";
		}
		else if (status == std::future_status::timeout) {
			std::cout << "timeout!\n";
		}
		else if (status == std::future_status::ready) {
			std::cout << "ready!\n";
		}
	} while (status != std::future_status::ready);

	std::cout << "result is " << f3.get() << std::endl;
}

int main(int agrn, char* argc[])
{
	return 0;
}
