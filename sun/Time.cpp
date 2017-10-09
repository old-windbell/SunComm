#include "stdafx.h"
#include "Time.h"

#include <ctime>

_SUN_BEGIN

Time::Time()
{
}


Time::~Time()
{
}

std::string Time::getTimeStr(bool asPath)
{
	std::time_t t = std::time(nullptr);
	std::tm* ptm = std::localtime(&t);
	char timebuf[32] = { 0 };
	if (asPath) {
		strftime(timebuf, sizeof timebuf, "%Y-%m-%d_%H-%M-%S", ptm);
	}
	else {
		strftime(timebuf, sizeof timebuf, "%Y-%m-%d %H:%M:%S", ptm);
	}

	return std::string(timebuf);
}

_SUN_END