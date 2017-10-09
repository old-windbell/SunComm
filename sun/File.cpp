#include "stdafx.h"
#include "File.h"

#include <cstring>

_SUN_BEGIN

FileDisk::FileDisk()
{

}


FileDisk::~FileDisk()
{

}

bool FileDisk::open(const std::string& name, FileDisk::OpenMode mode)
{
	fs_.open(name, mode);
	return fs_.is_open();
}

void FileDisk::close()
{
	fs_.close();
}

uint32 FileDisk::write(const char* s, uint32 count)
{
	fs_.write(s, count);
	return (uint32)(fs_.gcount());
}

uint32 FileDisk::read(char* buf, uint32 count)
{
	fs_.read(buf, count);
	return (uint32)(fs_.gcount());
}

uint32 FileDisk::tellRead()
{
	return (uint32)fs_.tellg();
}

uint32 FileDisk::tellWrite()
{
	return (uint32)fs_.tellp();
}

void FileDisk::seekRead(int32 off, SeekDir dir)
{
	fs_.seekg(off, (std::ios_base::seekdir)dir);
}

void FileDisk::seekWrite(int32 off, SeekDir dir)
{
	fs_.seekp(off, (std::ios_base::seekdir)dir);
}

void FileDisk::flush()
{
	fs_.flush();
}

//////////////////////////////////////////////////////////////////////////

FileMem::FileMem()
	: buf_(kInitialSize)
	, rpos_(0)
	, wpos_(0)
	, data_size_(0)
{
}

FileMem::~FileMem()
{

}

bool FileMem::open(const std::string& /*name*/, OpenMode /*mode*/)
{
	return true;
}

void FileMem::close()
{

}

uint32 FileMem::write(const char* s, uint32 count)
{
	ensureWritableBytes(count);
	std::memcpy(&buf_[wpos_], s, count);
	wpos_ += count;
	return count;
}

uint32 FileMem::read(char* buf, uint32 count)
{
	uint32 readCount = (readableBytes() >= count ? count : readableBytes());
	std::memcpy(buf, &buf[rpos_], readCount);
	rpos_ += readCount;
	return readCount;
}

uint32 FileMem::tellRead()
{
	return rpos_;
}

uint32 FileMem::tellWrite()
{
	return wpos_;
}

void FileMem::seekRead(int32 off, SeekDir dir)
{
	int64 pos = 0;
	if (FileBase::Beg == dir) {
		pos = off;
	}
	else if (FileBase::Cur == dir) {
		pos = rpos_ + off;
	}
	else if (FileBase::End == dir) {
		pos = off + data_size_;
	}

	if (pos < 0) {
		rpos_ = 0;
	}
	else if (pos > data_size_) {
		rpos_ = data_size_;
	}
	else {
		rpos_ = (uint32)pos;
	}
}

void FileMem::seekWrite(int32 off, SeekDir dir)
{
	int64 pos = 0;
	if (FileBase::Beg == dir) {
		pos = off;
	}
	else if (FileBase::Cur == dir) {
		pos = rpos_ + off;
	}
	else if (FileBase::End == dir) {
		pos = off + data_size_;
	}

	if (pos < 0) {
		wpos_ = 0;
	}
	else if (pos > buf_.size()) {
		ensureWritableBytes((uint32)pos);
		wpos_ = (uint32)pos;
	}
	else {
		rpos_ = (uint32)pos;
	}
}

void FileMem::ensureWritableBytes(uint32 len)
{
	if (writableBytes() < len)
	{
		makeSpace(len);
	}
}

void FileMem::makeSpace(uint32 len)
{
	if (writableBytes() < len) {
		uint32 doubleSize = 2 * buf_.size();
		uint32 neededSize = wpos_ + len;
		uint32 newSize = (doubleSize > neededSize ? doubleSize : neededSize);
		buf_.resize(newSize);
	}
}

_SUN_END