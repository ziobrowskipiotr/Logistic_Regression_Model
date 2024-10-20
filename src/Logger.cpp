#include "Logger.h"

// Constructor takes the message to log
Logger::Logger(const std::string& mess) {
    this->message = mess;  // Store a copy of the message
    logError();
}

// Function to get the current time in format YYYY-MM-DD HH:MM:SS
std::string Logger::getCurrentTime() {
    auto now = std::chrono::system_clock::now();
    std::time_t now_time = std::chrono::system_clock::to_time_t(now);
    
    std::tm* localTime = std::localtime(&now_time);

    std::stringstream ss;
    ss << std::put_time(localTime, "%Y-%m-%d %H:%M:%S");
    return ss.str();
}

// Function to log errors to logs.db
void Logger::logError() {
    this->return_code = sqlite3_open("database/logs.sqlite", &this->db);  // Open logs.db database
    if (this->return_code == SQLITE_OK) {
        // Safely prepare the SQL query
        std::string sql = "INSERT INTO logs (timestamp, message) VALUES (CURRENT_TIMESTAMP, ?);";
        sqlite3_stmt* stmt;
        this->return_code = sqlite3_prepare_v2(this->db, sql.c_str(), -1, &stmt, nullptr);

        if (this->return_code == SQLITE_OK) {
            sqlite3_bind_text(stmt, 1, message.c_str(), -1, SQLITE_STATIC);  // Insert the message
            this->return_code = sqlite3_step(stmt);  // Execute the query
        }

        sqlite3_finalize(stmt);  // Free resources
    }

    if (this->return_code != SQLITE_OK) {
        std::ofstream logFile;

        // Open file in append mode
        logFile.open("database/logs.txt", std::ios_base::app);
        logFile << "[" << getCurrentTime() << "], SQL error while inserting log to database: " << message << std::endl;
        logFile.close();
    }

    // Close the connection to the database (if it was opened)
    sqlite3_close(this->db);
}

// Destructor
Logger::~Logger() {}
