#include "utils.hpp"

std::string intToHexString(long input)
{
    std::stringstream ssHex;
    ssHex << std::hex << input;
    return "0x" + ssHex.str();
}