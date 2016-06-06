#define BOOST_TEST_MODULE "SessionPoolModule"
#include <boost/regex.hpp>
#include <boost/test/unit_test.hpp>
#include <boost/asio.hpp>
#include "../src/util.h"
#include "../src/virtualrealm.h"

static size_t count = 0;

bool grep_callback(const boost::match_results<const char*>& m) { count++; return true; }

BOOST_AUTO_TEST_CASE(UUID) {
  std::string str = SessionPool::GenerateUUID();
  boost::regex re("[0-9a-z]{8}-[0-9a-z]{4}-[0-9a-z]{4}-[0-9a-z]{4}-[0-9a-z]{12}");
  boost::regex_grep<bool (*)(const boost::cmatch&), const char*>(
      grep_callback, str.c_str(),
      str.c_str() + str.size(), re,
      boost::match_default | boost::match_partial);
  BOOST_CHECK_EQUAL(count, 1);
}

BOOST_AUTO_TEST_CASE(PollOne) {
  VirtualRealm::Ptr vr = VirtualRealm::Init(50000);
  vr->PollOne();
  BOOST_CHECK_EQUAL(1, 1);
}
