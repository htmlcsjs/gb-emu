
#include <string>
#include <vector>
#include "logging.hpp"

class Ram
{
private:
    std::vector<std::byte> storage;
    std::string sections;
    Logger *logger;
    std::string subsystem;
public:
    Ram(std::string romLocation, Logger *loggerPtr);
    std::byte read(uint16_t address);
    void write(uint16_t address, std::byte data);
    std::string info();
    ~Ram();
};

