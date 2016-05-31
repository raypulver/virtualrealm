#ifndef UTIL_H
#define UTIL_H

#include <string>
#include <cstring>
#include <cstdlib>
#include <cxxabi.h>

#define DEMANGLE_MAX_SIZE 0x400

template <typename T> char* demangle(T item) {
  const char *name;
  size_t len;
  int status;
  return abi::__cxa_demangle(typeid(item).name(), 0, 0, &status);
}

#endif
