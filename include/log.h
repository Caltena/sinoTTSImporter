#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <mutex>

class Logger
{
public:
    enum LogLevel
    {
        INFO,
        WARNING,
        ERROR
    };

    Logger(const std::string &filename)
    {

        try
        {
            logFile.open(filename, std::ios::app);
            if (!logFile.is_open())
            {
                std::cerr << "Could not open log file: " << filename << std::endl;
            }
        }
        catch (const std::exception &e)
        {
            std::cerr << "Caught general exception: " << e.what() << std::endl;
        }
        
    }

    ~Logger()
    {
        if (logFile.is_open())
        {
            logFile.close();
        }
    }

    void log(const std::string &message, LogLevel level)
    {
        std::lock_guard<std::mutex> guard(logMutex);
        if (logFile.is_open())
        {
            logFile << getCurrentTime() << " - [" << logLevelToString(level) << "] : " << message << std::endl;
        }
    }

private:
    std::ofstream logFile;
    std::mutex logMutex;

    std::string getCurrentTime()
    {
        std::time_t now = std::time(nullptr);
        char buf[100];
        std::strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", std::localtime(&now));
        return buf;
    }

    std::string logLevelToString(LogLevel level)
    {
        switch (level)
        {
        case INFO:
            return "INFO";
        case WARNING:
            return "WARNING";
        case ERROR:
            return "ERROR";
        default:
            return "UNKNOWN";
        }
    }
};

// Beispiel für die Verwendung der Logger-Klasse
/*
int main() {
    Logger logger("log.txt");

    logger.log("Programm gestartet", Logger::INFO);
    logger.log("Dies ist eine Warnung", Logger::WARNING);
    logger.log("Ein Fehler ist aufgetreten", Logger::ERROR);

    return 0;
}
*/
