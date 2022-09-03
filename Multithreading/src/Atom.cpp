#include <mutex>
#include <atomic>
#include <thread>

struct Counter
{
	int value;
	std::mutex mutex;

	void increment()
	{
		std::lock_guard<std::mutex> locker(mutex);
		++value;
	}

	void decrement()
	{
		std::lock_guard<std::mutex> locker(mutex);
		++value;
	}

	int get()
	{
		return value;
	}
};

struct AtomicCounter
{
	std::atomic<int> value;
	void increment()
	{
		++value;
	}

	void decrement()
	{
		--value;
	}

	int get()
	{
		return value;
	}
};

int main(int agrn, char* argc[])
{

}
