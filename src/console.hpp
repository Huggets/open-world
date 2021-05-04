#ifndef DEF_CONSOLE
#define DEF_CONSOLE

#include <string>

/*
   Contains functions that print message on the console.
 */
namespace console {
    /*
       Prints an error message in the console.
     */
    void error(const std::string& message);

    /*
       Prints a warning message in the console.
     */
    void warning(const std::string& message);

    /*
       Prints an info message in the console.
     */
    void info(const std::string& message);
}

#endif
