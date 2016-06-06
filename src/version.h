#ifndef VERSION_H
#define VERSION_H

#include <boost/format.hpp>

// version numbers
#define VIRTUALREALM_MAJOR_VERSION 0
#define VIRTUALREALM_MINOR_VERSION 1
#define VIRTUALREALM_BUILD_NUMBER 0
#define VIRTUALREALM_REVISION_NUMBER 1

extern const char *bnm;

inline std::string GetVersionString() {
  return (boost::format("%1% v%2%.%3%.%4%.%5%") % bnm % VIRTUALREALM_MAJOR_VERSION % VIRTUALREALM_MINOR_VERSION % VIRTUALREALM_BUILD_NUMBER % VIRTUALREALM_REVISION_NUMBER).str();
}

#endif
