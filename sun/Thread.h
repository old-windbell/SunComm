#pragma once

#include <functional>

#include "GlobalDef.h"
#include "Types.h"

namespace std
{
	class thread;
}

_SUN_BEGIN

class Thread
{
public:
	// function the thread run
	typedef std::function<void ()> ThreadFunc;

	// ctor of Thread
	Thread(const ThreadFunc& func, const std::string& name = "");

	~Thread();

	void start();
	void join();

	// thread name passed in ctor
	const std::string& name() { return name_; }

	// thread id string
	std::string idString();

private:
	bool started_;
	std::thread* thread_;
	ThreadFunc func_;
	std::string name_;
};

_SUN_END