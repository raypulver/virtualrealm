#include <boost/exception/all.hpp>
#include <cstdio>
#include "exception.h"
Exception::Exception() {
  Zero();
  snprintf(message, sizeof(message), format);
}
const char *Exception::what() const noexcept {
  return const_cast<const char *>(message);
}
