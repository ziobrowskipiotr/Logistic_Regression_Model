#ifndef LOGGER_H
#define LOGGER_H

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <sqlite3.h>
#include <chrono>
#include <iomanip>
#include <ctime>

class Logger {
private:
    sqlite3* db;
    int return_code;
    std::string message;  // Changed to std::string instead of a pointer

public:
    // Constructor takes the message to log
    Logger(const std::string& mess);  // Changed to const & for optimization

    // Function to log errors into logs.db
    void logError();

private:
    // Function to get the current time in format YYYY-MM-DD HH:MM:SS
    std::string getCurrentTime();
    
public:
    // Destructor
    ~Logger();
};

#endif  // LOGGER_H
