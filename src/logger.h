#ifndef LOGGER_H
#define LOGGER_H
#include "formatter.h"
#include <string>
#define MAX_LOG_MSG 0x10000
class Logger {
  LogFormatter formatter;
  public:
  Logger() = default;
  void Critical(std::string);
  void Warn(std::string);
  void Log(std::string);
};
extern Logger logger;
#endif
