#include "stdafx.h"

#include <sstream>

#include "ThreadPool.h"
#include "Logging.h"

_USING_SUN;

void print()
{
	std::stringstream ss;
	ss << std::this_thread::get_id();
	LOG_INFO << ss.str();
}

void printString(const std::string& str)
{
	LOG_INFO << str;
	std::this_thread::sleep_for(std::chrono::milliseconds(10));
}

void test(uint32 maxSize)
{
	LOG_WARN << "Test ThreadPool with max queue size = " << maxSize;
	ThreadPool pool("MainThreadPool");
	pool.setMaxQueueSize(maxSize);
	pool.start(4);

	ThreadPool::ThreadTask tt;

	LOG_WARN << "Adding";
	pool.run(&print);
	pool.run(&print);
	for (int i = 0; i < 100; ++i)
	{
		char buf[32];
		snprintf(buf, sizeof buf, "task %d", i);
		pool.run(std::bind(printString, std::string(buf)));
	}
	LOG_WARN << "Done";

	pool.stop();
}

void ThreadPool_Test()
{
	test(0);
	test(1);
	test(5);
	test(10);
 	test(50);
}