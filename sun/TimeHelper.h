#pragma once

#include "GlobalDef.h"
#include "Types.h"

_SUN_BEGIN

class TimeHelper
{
public:
	TimeHelper();
	~TimeHelper();

	static std::string getTimeStr(bool asPath = false);
};

_SUN_END