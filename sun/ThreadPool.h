#pragma once

#include <queue>
#include <mutex>
#include <vector>
#include <condition_variable>
#include <functional>

#include "GlobalDef.h"
#include "Types.h"

_SUN_BEGIN
class Thread;

class ThreadPool
{
public:
	typedef std::function<void()> ThreadTask;

	ThreadPool(const std::string& name);
	~ThreadPool();

	void setMaxQueueSize(uint32 size) { maxTaskSize_ = size; }
	uint32 getMaxQueueSize() const { return maxTaskSize_; }

	void start(int32 threadsNum);
	void stop();
	void run(ThreadTask& task);
	void run(ThreadTask&& task);

private:
	ThreadTask take();
	void doTask();

private:
	std::string name_;
	std::queue<ThreadTask> tasks_;
	std::vector<Thread*> threads_;
	uint32 maxTaskSize_;
	bool stop_;

	std::condition_variable hasTask_;
	std::condition_variable hasSpace_;
	std::mutex mutex_;
};

_SUN_END