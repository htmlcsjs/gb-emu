#include <fstream>
#include <chrono>
#include <ctime>
#include "logging.hpp"

Logger::Logger(std::string name, bool logToFile, int levelMin)
{
    initlised = true;
    fileMode = logToFile;
    programName = name;
    minLevel = levelMin;
    levelMap = {
        {0, "Debug"},
        {1, "Normal"},
        {2, "Warning"},
        {3, "Error"},
        {4, "Fatal Error"},
    };
    if (fileMode)
    {
        logFile.open(programName + ".log");
    }
    log(1, programName + " Logger", "Logging started");
}

Logger::~Logger()
{
}

void Logger::log(int level, std::string section, std::string msg)
{
    if (level < minLevel && initlised)
    {
        return;
    }
    else if (fileMode && initlised)
    {
        std::time_t now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
        std::string timeStr(ctime(&now));
        logFile << "[" << timeStr.substr(0, timeStr.length() - 1) << "][" << levelMap[level] << "][" << section << "] " << msg << "\n";
    }
    else if (initlised)
    {
        std::time_t now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
        std::string timeStr(ctime(&now));
        std::cout << "[" << timeStr.substr(0, timeStr.length() - 1) << "][" << levelMap[level] << "][" << section << "] " << msg << "\n";
    }
    
}