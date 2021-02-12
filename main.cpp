#include <iostream>
#include <fstream>
#include "ram.hpp"
#include <string>

int main(int argc, char const *argv[])
{
    Ram test = Ram("cpu_instrs.gb");
    std::cout << test.info() << "\n";
    /* code */
    return 0;
}