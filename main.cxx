#include <iostream>
#include "driver.hxx"

int main (int argc, char *argv[])
{
    int res = 0;
    yy::driver drv;

    for (int i = 1; i < argc; ++i)
    {
        if (argv[i] == std::string ("-p"))
            drv.trace_parsing_ = true;
        else if (argv[i] == std::string ("-s"))
            drv.trace_scanning_ = true;
        else if (drv.parse(argv[i]))
            res = 1;
    }

    return res;
}
