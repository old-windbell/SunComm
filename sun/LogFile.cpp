#include "stdafx.h"
#include "LogFile.h"

#include "File.h"

_SUN_BEGIN


LogFile::LogFile(const std::string& name, 
				uint32 rollSize, 
				uint32 flushInterval,
				bool threadSafe)
	: name_(name)
	, rollSize_(rollSize)
	, flushInterval_(flushInterval)
	, mutex_(threadSafe ? new std::mutex() : nullptr)
	, lastRoll_(0)
{
	rollFile();
}

LogFile::~LogFile()
{
}

void LogFile::append(const char* s, uint32 len)
{
	if (mutex_) {
		std::lock_guard<std::mutex> lock(*mutex_);
		write(s, len);
	}
	else {
		write(s, len);
	}
}

void LogFile::write(const char* s, uint32 len)
{
	file_->write(s, len);
	if (file_->tellWrite() >= rollSize_) {
		rollFile();
	}
}

void LogFile::flush()
{
	if (mutex_) {
		std::lock_guard<std::mutex> lock(*mutex_);
		file_->flush();
	}
	else {
		file_->flush();
	}
}

bool LogFile::rollFile()
{
	std::time_t now;
	std::string filename = getLogFileName(name_, now);
	if (now > lastRoll_) {
		lastRoll_ = now;
		file_.reset(new FileDisk());
		return file_->open(filename, FileBase::WRITE);
	}

	return false;
}

std::string LogFile::getLogFileName(const std::string& name, std::time_t& t)
{
	std::string filename;
	filename.reserve(name.size() + 64);
	filename = name;

	t = std::time(nullptr);
	std::tm* ptm = std::localtime(&t);
	char timebuf[32];
	strftime(timebuf, sizeof timebuf, "%Y-%m-%d_%H-%M-%S", ptm);
	filename += timebuf;

	filename += ".log";

	return filename;
}

_SUN_END