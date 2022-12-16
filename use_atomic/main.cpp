#include <iostream>
#include <memory>
#include <thread>
#include <vector>
#include <atomic>
#include <utility>

using namespace std;

class Stopwatch
{
	std::chrono::high_resolution_clock::time_point t1;
	std::chrono::high_resolution_clock::time_point t2;

public:
	Stopwatch()
	{
		start();
	}

	void start()
	{
		t1 = std::chrono::high_resolution_clock::now();
	}

	double stop()
	{
		t2 = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double, std::milli> elapsed = t2 - t1;
		return elapsed.count();
	}
};

class ThreadPool
{
	std::vector<std::shared_ptr<std::thread>> threads;

public:
	ThreadPool()
	{
		threads.reserve(100);
	}

	template<class FuncPtr, class InstancePtr>
	void start(const int threadCount, FuncPtr func, InstancePtr ptr)
	{
		for (int i = 0; i < threadCount; ++i)
		{
			threads.push_back(std::make_shared<std::thread>(func, ptr));
		}
	}

	void stop()
	{
		for (auto& th : threads)
		{
			th->join();
			th.reset();
		}
		threads.clear();
	}

	void joinAll()
	{
		for (auto& th : threads)
		{
			th->join();
		}
	}
};

class Counter
{
public:
	std::atomic_long cnt;

	Counter()
		: cnt(0)
	{

	}

	void count()
	{
		for (int i = 0; i < 100000; i++)
		{
			cnt += 1;
		}
	}
};

struct A
{
	int a[100];
};
struct B
{
	int x, y;
};

void print_lock_free()
{
	std::cout << std::boolalpha
			  << "std::atomic_bool is lock free? " << std::atomic_bool{}.is_lock_free() << std::endl
			  << "std::atomic_int8_t is lock free? " << std::atomic_int8_t{}.is_lock_free() << std::endl
			  << "std::atomic_int16_t is lock free? " << std::atomic_int16_t{}.is_lock_free() << std::endl
			  << "std::atomic_int32_t is lock free? " << std::atomic_int32_t{}.is_lock_free() << std::endl
			  << "std::atomic_int64_t is lock free? " << std::atomic_int64_t{}.is_lock_free() << std::endl
			  << "std::atomic_uint8_t is lock free? " << std::atomic_uint8_t{}.is_lock_free() << std::endl
			  << "std::atomic_uint16_t is lock free? " << std::atomic_uint16_t{}.is_lock_free() << std::endl
			  << "std::atomic_uint32_t is lock free? " << std::atomic_uint32_t{}.is_lock_free() << std::endl
			  << "std::atomic_uint64_t is lock free? " << std::atomic_uint64_t{}.is_lock_free() << std::endl
			  << "std::atomic<A> is lock free? " << std::atomic<A>{}.is_lock_free() << std::endl// 需要链接atomic库
			  << "std::atomic<B> is lock free? " << std::atomic<B>{}.is_lock_free() << std::endl;
}

int main(int argc, char* argv[])
{
	ThreadPool threadPool;
	Counter counter;
	Stopwatch stopwatch;

	threadPool.start(100, &Counter::count, &counter);
	threadPool.joinAll();

	std::cout << "result: " << counter.cnt << std::endl;
	std::cout << "duration: " << stopwatch.stop() << " ms" << std::endl;

	print_lock_free();

	return 0;
}
