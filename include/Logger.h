#ifndef LOGGER_H
#define LOGGER_H

#include <ctime>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

enum LogLevel { DEBUG, INFO, WARNING, ERROR, CRITICAL };

class Logger {
public:
    Logger(const string& filename);
    ~Logger();

    void log(LogLevel lvl, const string& message);

private:
    ofstream logFile;

    string levelToString(LogLevel level);
};

#endif // LOGGER_H
