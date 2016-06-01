#ifndef EXCEPTION_H
#define EXCEPTION_H
#include <boost/exception/all.hpp>
#include <exception>

#define MAX_EXCEPTION_MESSAGE_LENGTH 0x400

class Exception : public boost::exception, public std::exception {
  char message[MAX_EXCEPTION_MESSAGE_LENGTH];
  inline void Zero() {
    memset(message, 0, sizeof(message));
  }
  protected:
    static constexpr const char *const format = "%s";
  public:
  template <typename T, typename... Args> Exception(T first, Args ...rest) {
    Zero();
    snprintf(message, sizeof(message), format, first, rest...);
  }
  template <typename T> Exception(T arg) {
    Zero();
    snprintf(message, sizeof(message), format, arg);
  }
  Exception();
  virtual const char *what() const noexcept;
};

class TerminfoException : public Exception {
  using Exception::Exception;
};

#endif
