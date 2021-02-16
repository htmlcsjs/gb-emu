#include "utils.hpp"

std::string intToHexString(long input)
{
    std::stringstream ssHex;
    ssHex << std::hex << input;
    return "0x" + ssHex.str();
}

std::string intToBinString(long input)
{
    return "0b" + std::bitset<8>(input).to_string();
}