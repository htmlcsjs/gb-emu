#include <string>
#include <iostream>
#include <fstream>
#include <map>

class Logger
{
private:
    std::string programName;
    bool fileMode;
    std::ofstream logFile;
    std::map<int, std::string> levelMap;
    int minLevel;
    bool initlised;
public:
    Logger(std::string name, bool logToFile = false, int levelMin = 1);
    Logger();
    void init(std::string name, bool logToFile = false, int levelMin = 1);
    ~Logger();
    void log(int level, std::string section, std::string msg);
};