#pragma once
#include <string>
#include <vector>
#include "logging.hpp"
#include "utils.hpp"

typedef uint16_t u16;
typedef uint8_t u8;

class Ram
{
private:
    std::vector<std::byte> storage;
    std::string sections;
    Logger *logger;
    std::string subsystem;
public:
    Ram(std::string romLocation, Logger *loggerPtr);
    std::byte read(u16 address);
    void write(u16 address, std::byte data);
    std::string info();
    ~Ram();
};
