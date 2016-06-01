#include <curses.h>
#include <term.h>
#include <cstdlib>
#include <iostream>
#include <string>
#include "exception.h"
#include "formatter.h"

LogFormatter::LogFormatter() {
    int status;
    used_term = false;
    if (!setupterm((char *) 0, 1, (int *) 0)) used_term = true;
    switch ((status = tigetnum("colors"))) {
      case -2:
        throw TerminfoException("colors not a numeric capability.");
        break;
      case -1:
        throw TerminfoException("colors field absent from terminfo database");
        break;
      default:
        if (status) has_color = true;
        std::cout << status << std::endl;
        break;
    }
}

