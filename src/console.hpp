#ifndef DEF_CONSOLE
#define DEF_CONSOLE

#include <string>

/*
   Contain functions that print message on the console.
   */
namespace console {
    /*
       Print an error message in the console.
       */
    void error(std::string message);

    /*
       Print a warning message in the console.
       */
    void warning(std::string message);

    /*
       Print an info message in the console.
       */
    void info(std::string message);
}

#endif
