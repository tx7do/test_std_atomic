#include <iostream>
#include <memory>
#include <thread>
#include <vector>
#include <mutex>

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
	long cnt{ 0 };
	std::mutex mtx;

	Counter() = default;

	void count()
	{
		for (int i = 0; i < 100000; i++)
		{
			std::lock_guard<std::mutex> lock(mtx);
			cnt += 1;
		}
	}
};

int main(int argc, char* argv[])
{
	ThreadPool threadPool;
	Counter counter;
	Stopwatch stopwatch;

	threadPool.start(100, &Counter::count, &counter);
	threadPool.joinAll();

	std::cout << "result: " << counter.cnt << std::endl;
	std::cout << "duration: " << stopwatch.stop() << " ms" << std::endl;

	return 0;
}
