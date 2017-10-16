#include "stdafx.h"
#include "ThreadPool.h"

#include <limits>

#include "Thread.h"
#include "Logging.h"

_SUN_BEGIN

ThreadPool::ThreadPool(const std::string& name)
	: name_(name)
	, maxTaskSize_(std::numeric_limits<int32>::max())
	, stop_(false)
{
}

ThreadPool::~ThreadPool()
{
	if (!stop_) {
		stop();
	}
}

void ThreadPool::start(int32 threadsNum)
{
	for (int i = 0; i < threadsNum; ++i) {
		std::string name = name_ + '_' + std::to_string(i);
		Thread* p = new Thread(std::bind(&ThreadPool::doTask, this), name);
		threads_.push_back(p);
		p->start();
	}
}

void ThreadPool::stop()
{
	mutex_.lock();
	stop_ = true;
	hasTask_.notify_all();
	mutex_.unlock();

	std::for_each(threads_.begin(), threads_.end(), 
				  std::bind(&Thread::join, std::placeholders::_1));
}

void ThreadPool::run(ThreadTask& task)
{
	if (threads_.empty()) {
		task();
	}
	else {
		std::unique_lock<std::mutex> lock(mutex_);
		while (maxTaskSize_ > 0 && tasks_.size() >= maxTaskSize_)
		{
			hasSpace_.wait(lock);
		}

		tasks_.push(task);
		hasTask_.notify_one();
	}
}

void ThreadPool::run(ThreadTask&& task)
{
	if (threads_.empty()) {
		task();
	}
	else {
		std::unique_lock<std::mutex> lock(mutex_);
		while (maxTaskSize_ > 0 && tasks_.size() >= maxTaskSize_)
		{
			hasSpace_.wait(lock);
		}

		tasks_.push(std::move(task));
		hasTask_.notify_one();
	}
}

ThreadPool::ThreadTask ThreadPool::take()
{
	std::unique_lock<std::mutex> lock(mutex_);
	while (!stop_ && tasks_.empty()) {
		hasTask_.wait(lock);
	}

	ThreadTask task;
	if (!tasks_.empty()) {
		task = tasks_.front();
		tasks_.pop();
		if (maxTaskSize_ > 0) {
			hasSpace_.notify_one();
		}
	}
	
	return task;
}

void ThreadPool::doTask()
{
	try {
		while (!stop_) {
			ThreadTask task(take());
			if (task) {
				task();
			}
		}
	}
	catch (const std::exception& e) {
		LOG_TRACE << "exception caught in ThreadPool" << name_
			<< "reason:" << e.what();
		//abort();
	}
	catch (...) {
		LOG_TRACE << "unknown exception caught in ThreadPool" << name_;
		throw;
	}
}


_SUN_END