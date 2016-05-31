#include <boost/config/warning_disable.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/include/phoenix_object.hpp>
#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/fusion/include/io.hpp>
#include <cstdlib>
#include <iostream>
#include <string>

class LogFormatter {
  static bool has_color;
  static void Init() {
    char *term;
    has_color = false;
    if (term = getenv("TERM")) {

