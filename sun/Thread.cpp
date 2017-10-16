#include "stdafx.h"
#include "Thread.h"

#include <thread>
#include <sstream>

_SUN_BEGIN

Thread::Thread(const ThreadFunc& func, const std::string& name)
	: started_(false)
	, thread_(nullptr)
	, name_(name)
	, func_(func)
{
}

Thread::~Thread()
{
	deletePtr(thread_);
}

void Thread::start()
{
	if (!started_) {
		thread_ = new std::thread(func_);
	}
}

void Thread::join()
{
	if (started_) {
		thread_->join();
	}
}

std::string Thread::idString()
{
	if (nullptr != thread_) {
		std::stringstream ss;
		ss << thread_->get_id();
		return ss.str();
	}

	return std::string();
}

_SUN_END