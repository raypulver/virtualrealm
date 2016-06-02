#ifndef UTIL_H
#define UTIL_H

#include <cxxabi.h>
#include <cstdlib>
#include <cstring>
#include <memory>
#include <string>

#define DEMANGLE_MAX_SIZE 0x400

namespace Util {

template <typename T>
char* demangle(T item) {
  const char* name;
  size_t len;
  int status;
  return abi::__cxa_demangle(typeid(item).name(), 0, 0, &status);
}
}

#endif
