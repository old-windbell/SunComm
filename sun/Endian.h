#pragma once

#include "GlobalDef.h"
#include "Types.h"

_SUN_BEGIN

class Endian
{
public:
	Endian() = default;
	virtual ~Endian() {}

public:
	static uint16 swap16(uint16 val) {
		return (val << 8 | val >> 8);
	}
	static uint32 swap32(uint32 val) {
		return ((val << 24) | (val >> 24) \
			| ((val << 8) & 0x00ff0000) \
			| ((val >> 8) & 0x0000ff00));
	}

public:
	virtual uint16 value16(uint16 val) = 0;
	virtual uint32 value32(uint32 val) = 0;
};

class BigEndian : public Endian
{
public:
	uint16 value16(uint16 val) override {
#ifdef ARCH_BIG_ENDIAN
		return val;
#else
		return swap16(val);
#endif // ARCH_BIG_ENDIAN
	}

	uint32 value32(uint32 val) override {
#ifdef ARCH_BIG_ENDIAN
		return val;
#else
		return swap32(val);
#endif // ARCH_BIG_ENDIAN
	}
};

class LittleEndian : public Endian
{
public:
	uint16 value16(uint16 val) override {
#ifdef ARCH_BIG_ENDIAN
		return swap16(val);
#else
		return val;
#endif // ARCH_BIG_ENDIAN
	}

	uint32 value32(uint32 val) override {
#ifdef ARCH_BIG_ENDIAN
		return swap32(val);
#else
		return val;
#endif // ARCH_BIG_ENDIAN
	}
};

_SUN_END