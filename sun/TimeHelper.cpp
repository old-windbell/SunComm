#include "stdafx.h"
#include "TimeHelper.h"

#include <ctime>

_SUN_BEGIN

TimeHelper::TimeHelper()
{
}


TimeHelper::~TimeHelper()
{
}

std::string TimeHelper::getTimeStr(bool asPath)
{
	std::time_t t = std::time(nullptr);
	std::tm* ptm = std::localtime(&t);
	char timebuf[32] = { 0 };
	if (asPath) {
		std::strftime(timebuf, sizeof timebuf, "%Y-%m-%d_%H-%M-%S", ptm);
	}
	else {
		std::strftime(timebuf, sizeof timebuf, "%Y-%m-%d %H:%M:%S", ptm);
	}

	return std::string(timebuf);
}

_SUN_END