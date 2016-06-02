#ifndef EXCEPTION_H
#define EXCEPTION_H
#include <boost/exception/all.hpp>
#include <cstdint>
#include <cstring>
#include <exception>
#include "util.h"

#define MAX_EXCEPTION_MESSAGE_LENGTH 0x400

enum ErrorCode {
  BASE_ERROR = 0xff000000,
  AUTH_FAILURE = 0x10000000,
  MESSAGE_MALFORMED = 0x20000000,
  TERMINFO_INCAPABLE = 0x00010001,
  TERMINFO_COLOR_ABSENT = 0x00010002,
  USER_NOT_FOUND = 0x0000001,
  INVALID_PASS = 0x00000002,
  TOKEN_EXPIRED = 0x00000004,
  TOKEN_INVALID = 0x00000008,
};

class ErrorCodeTag;

typedef boost::error_info<ErrorCodeTag, uint32_t> ErrorCodeInfo;

class Exception : public boost::exception, public std::exception {
  std::string message;
 public:
  Exception(std::string msg);
  virtual const char *what() const noexcept;
};

class TerminfoException : public Exception {
  using Exception::Exception;
};

#endif
