#include <vector>
#include <string>

class Ram
{
private:
    std::vector<std::byte> storage;
    std::string sections;
public:
    Ram(std::string romLocation);
    std::byte read(uint16_t address);
    void write(uint16_t address, std::byte data);
    std::string info();
    ~Ram();
};

