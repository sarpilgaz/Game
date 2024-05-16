#include "Logger.h"

Logger::Logger(const string& filename) {
    logFile.open(filename, ios::app);
    if (!logFile.is_open()) {
        cerr << "Failed to open file" << endl;
    }
}

Logger::~Logger() {
    logFile.close();
}

void Logger::log(LogLevel lvl, const string& message) {
    time_t now = time(0);
    tm* timeinfo = localtime(&now);
    char timestamp[20];
    strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", timeinfo);

    ostringstream logmsg;
    logmsg << "[" << timestamp << "]" << levelToString(lvl) << ": " << message << endl;

    if (logFile.is_open()) {
        logFile << logmsg.str();
        logmsg.flush();
    }
}

string Logger::levelToString(LogLevel level) {
    switch (level) {
        case DEBUG:
            return "DEBUG";
        case INFO:
            return "INFO";
        case WARNING:
            return "WARNING";
        case ERROR:
            return "ERROR";
        case CRITICAL:
            return "CRITICAL";
        default:
            return "UNKNOWN";
    }
}
