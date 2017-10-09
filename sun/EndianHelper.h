#pragma once

#include <memory>

#include "GlobalDef.h"
#include "Types.h"

_SUN_BEGIN

class Endian;
class FileBase;

class EndianHelper
{
public:
	EndianHelper(FileBase& f, bool bigEndian);
	EndianHelper(FileBase& f, Endian* endian);
	~EndianHelper();

public:
	void storeU8(uint8 v);
	void storeU16(uint16 v);
	void storeU32(uint32 v);
	uint32 storeData(const char* data, uint32 size);

	uint8 loadU8();
	uint16 loadU16();
	uint32 loadU32();
	uint32 loadData(char* buf, uint32 size);

private:
	FileBase& file_;
	std::unique_ptr<Endian> endian_;
};

_SUN_END