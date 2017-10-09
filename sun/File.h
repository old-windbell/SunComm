#pragma once

#include "GlobalDef.h"
#include "Types.h"
#include <string>
#include <fstream>
#include <vector>

_SUN_BEGIN

class FileBase
{
public:
	enum OpenMode {
		READ = std::ios_base::in,
		WRITE = std::ios_base::out,
		READWRITE = READ | WRITE,
		BINARY
	};

	enum SeekDir {
		Beg = std::ios_base::beg,
		End = std::ios_base::end,
		Cur = std::ios_base::cur,
	};

public:
	FileBase() {}
	virtual ~FileBase() {}

public:
	virtual bool open(const std::string& name, OpenMode mode) = 0;
	virtual void close() = 0;
	virtual uint32 write(const char* s, uint32 count) = 0;
	virtual uint32 read(char* buf, uint32 count) = 0;
	virtual uint32 tellRead() = 0;
	virtual uint32 tellWrite() = 0;
	virtual void seekRead(int32 off, SeekDir dir) = 0;
	virtual void seekWrite(int32 off, SeekDir dir) = 0;
};


class FileDisk : public FileBase
{
public:
	FileDisk();
	virtual ~FileDisk();

public:
	bool open(const std::string& name, OpenMode mode) override;
	void close() override;
	uint32 write(const char* s, uint32 count) override;
	uint32 read(char* buf, uint32 count) override;
	uint32 tellRead() override;
	uint32 tellWrite() override;
	void seekRead(int32 off, SeekDir dir) override;
	void seekWrite(int32 off, SeekDir dir) override;

public:
	void flush();

private:
	std::fstream fs_;
};


class FileMem : public FileBase
{
public:
	static const size_t kInitialSize = 1024;

	FileMem();
	virtual ~FileMem();

public:
	bool open(const std::string& name = "", OpenMode mode = READWRITE) override;
	void close() override;
	uint32 write(const char* s, uint32 count) override;
	uint32 read(char* buf, uint32 count) override;
	uint32 tellRead() override;
	uint32 tellWrite() override;
	void seekRead(int32 off, SeekDir dir) override;
	void seekWrite(int32 off, SeekDir dir) override;

public:
	uint32 readableBytes() const { return wpos_ - rpos_; }
	uint32 writableBytes() const { return buf_.size() - wpos_; }
	char* data() { return buf_.data(); }
	const char* data() const { return buf_.data(); }

private:
	void ensureWritableBytes(uint32 len);
	void makeSpace(uint32 len);

private:
	std::vector<char> buf_;
	uint32 rpos_;	//reader position
	uint32 wpos_;	//writer position
	uint32 data_size_;
};

_SUN_END