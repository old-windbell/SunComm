
#include "stdafx.h"

#include "LogFile.h"
#include "Logging.h"

std::unique_ptr<sun::LogFile> g_logFile;

void outputFunc(const char* msg, int len)
{
  g_logFile->append(msg, len);
}

void flushFunc()
{
  g_logFile->flush();
}

void LogFile_Test(const std::string& path)
{
  g_logFile.reset(new sun::LogFile(path, 200*1000));
  sun::Logger::setOutput(outputFunc);
  sun::Logger::setFlush(flushFunc);

  std::string line = "1234567890 abcdefghijklmnopqrstuvwxyz ABCDEFGHIJKLMNOPQRSTUVWXYZ ";

  for (int i = 0; i < 100; ++i)
  {
    LOG_INFO << line << i;

// 	using namespace std::chrono_literals;
// 	std::this_thread::sleep_for(2s);
  }
}
