#pragma once

#include <mutex>
#include <memory>
#include <ctime>

#include "GlobalDef.h"
#include "Types.h"


_SUN_BEGIN

class FileDisk;

class LogFile
{
public:
	LogFile(const std::string& name, 
			uint32 rollSize = 128 * KB,
			uint32 flushInterval = 4,	//seconds
			bool threadSafe = true);
	~LogFile();

	void append(const char* s, uint32 len);
	void flush();
	bool rollFile();

private:
	void write(const char* s, uint32 len);
	static std::string getLogFileName(const std::string& name, std::time_t& t);

private:
	const std::string name_;
	const uint32 rollSize_;
	const uint32 flushInterval_;

	std::time_t lastRoll_;
	std::unique_ptr<std::mutex> mutex_;
	std::unique_ptr<FileDisk> file_;
};

_SUN_END