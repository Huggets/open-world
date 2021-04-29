#ifndef DEF_CONSOLE
#define DEF_CONSOLE

#include <string>

/*
   Contain only statics functions to print message on the console.
   */
class Console {
    public:
        /*
           Print an error message in the console.
           */
        static void error(std::string message);

        /*
           Print a warning message in the console.
           */
        static void warning(std::string message);

        /*
           Print an info message in the console.
           */
        static void info(std::string message);
};
#endif
