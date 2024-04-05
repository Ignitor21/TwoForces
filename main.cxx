#include <iostream>
#include <string>
#include "driver.hxx"

int main (int argc, char *argv[])
{
    if (argc < 2)
    {
        std::cerr << "Missing argument - name of file\n";
        return -1;
    }

    int res = 0;
    yy::driver drv;

    for (int i = 1; i < argc; ++i)
    {
        if (argv[i] == std::string ("-p"))
            drv.set_parse_debug_level(true);
        else if (argv[i] == std::string ("-s"))
            drv.set_scan_debug_level(true);
        else
            res = drv.parse(argv[i]);
    }

    return res;
}
