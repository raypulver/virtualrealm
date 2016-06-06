#include <libgen.h>
#include <getopt.h>
#include <string>
#include <boost/format.hpp>
#include <boost/regex.hpp>
#include <iostream>
#include <cctype>
#include "virtualrealm.h"
#include "version.h"

const char *bnm;

std::string usage;

#define USAGE_LEFT_ADJUST 10 
#define USAGE_COLUMN_WIDTH 20

static void ConstructUsageString() {
  std::stringstream uss;
  std::string strfmt ((boost::format("       %%|-%1%| %%|-%2%| %%|-%2%|") % USAGE_LEFT_ADJUST % USAGE_COLUMN_WIDTH).str());
  uss << boost::format("Usage: %1% [-vh] [-p PORT]") % bnm << std::endl;
  uss << boost::format(strfmt.c_str()) % "-p [PORT]," % "--port=[PORT]" % "specify port" << std::endl;
  uss << boost::format(strfmt.c_str()) % "-h," % "--help" % "display this help" << std::endl;
  uss << boost::format(strfmt.c_str()) % "-v," % "--version" % "display version number";
  usage = uss.str();
}

int main(int argc, char **argv) {
  int c, long_index;
  short port;
  static struct option long_options[] = {
    {"port", required_argument, 0, 'p'},
    {"help", no_argument, 0, 'h'},
    {"version", no_argument, 0, 'v'},
    {0, 0, 0, 0}
  };
  static boost::regex re("^\\d+$");
  bnm = basename(argv[0]);
  port = 50000;
  ConstructUsageString();
  while ((c = getopt_long(argc, argv, "p:vh", long_options, &long_index)) != -1) {
    switch (c) {
      case 'p':
        if (!boost::regex_match(optarg, re, boost::match_default)) {
          std::cerr << boost::format("%1%: port must be an integer") % bnm << std::endl;
          std::cerr << usage << std::endl;
          return 1;
        }
        port = atoi(optarg);
        break;
      case 'v':
        std::cout << GetVersionString() << std::endl;
        return 1;
        break;
      case 'h':
        std::cout << usage << std::endl;
        return 1;
        break;
      case '?':
        std::cerr << usage << std::endl;
        return 1;
        break;
    }
  }
  while (optind < argc) {
    ++optind;
  }
  VirtualRealm::Ptr vr = VirtualRealm::Init(port);
  vr->Run();
  return 0;
}
