#pragma once

#include "GlobalDef.h"
#include "Types.h"

_SUN_BEGIN

class Time
{
public:
	Time();
	~Time();

	static std::string getTimeStr(bool asPath = false);
};

_SUN_END