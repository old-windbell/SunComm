#include "stdafx.h"
#include "EndianHelper.h"

#include "Endian.h"
#include "File.h"

_SUN_BEGIN

EndianHelper::EndianHelper(FileBase& f, bool bigEndian)
	: file_(f)
{
	if (bigEndian) {
		endian_.reset(new BigEndian());
	}
	else {
		endian_.reset(new LittleEndian());
	}
}

EndianHelper::EndianHelper(FileBase& f, Endian* endian)
	: file_(f)
	, endian_(endian)
{
	assert_s(nullptr != endian_.get());
}

EndianHelper::~EndianHelper()
{
}


void EndianHelper::storeU8(uint8 v)
{
	uint32 size = storeData((const char*)&v, sizeof(uint8));
	assert_s(sizeof(uint8) == size);
}

void EndianHelper::storeU16(uint16 v)
{
	v = endian_->value16(v);
	uint32 size = storeData((const char*)&v, sizeof(uint16));
	assert_s(sizeof(uint16) == size);
}

void EndianHelper::storeU32(uint32 v)
{
	v = endian_->value32(v);
	uint32 size = storeData((const char*)&v, sizeof(uint32));
	assert_s(sizeof(uint32) == size);
}

uint32 EndianHelper::storeData(const char * data, uint32 size)
{
	return file_.write(data, size);
}

uint8 EndianHelper::loadU8()
{
	uint8 v = 0;
	uint32 size = file_.read((char*)&v, sizeof(v));
	assert_s(sizeof(v) == size);
	return v;
}

uint16 EndianHelper::loadU16()
{
	uint16 v = 0;
	uint32 size = file_.read((char*)&v, sizeof(v));
	assert_s(sizeof(v) == size);
	return endian_->value16(v);
}

uint32 EndianHelper::loadU32()
{
	uint32 v = 0;
	uint32 size = file_.read((char*)&v, sizeof(v));
	assert_s(sizeof(v) == size);
	return endian_->value32(v);
}

uint32 EndianHelper::loadData(char * buf, uint32 size)
{
	return file_.read(buf, size);
}


_SUN_END