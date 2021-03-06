#include <boost/cstdint.hpp>
#include <boost/exception/all.hpp>
#include <cstdio>
#include <cstring>
#include "exception.h"

Exception::Exception(std::string msg) : message(msg) {}

const char *Exception::what() const noexcept {
  return message.c_str();
}
