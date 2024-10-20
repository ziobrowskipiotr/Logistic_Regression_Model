#include <gtest/gtest.h>
#include "Logger.h"
#include <fstream>
#include <string>
#include <filesystem>  // C++17 feature to manipulate files and directories

namespace fs = std::filesystem;

// Helper function to check if a file exists
bool fileExists(const std::string& filename) {
    std::ifstream file(filename);
    return file.good();
}

// Helper function to read the contents of a file
std::string readFileContents(const std::string& filename) {
    std::ifstream file(filename);
    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

// Test for logging to a file when the database fails
TEST(LoggerTest, LogsToFileWhenDatabaseFails) {

    // Create a Logger instance with a test message
    std::string testMessage = "This is a test error message";
    Logger logger(testMessage);

    // Check if the file has been created
    EXPECT_TRUE(fileExists("database/logs.txt"));

    // Check if the file contains the correct message
    std::string fileContents = readFileContents("database/logs.txt");
    EXPECT_NE(fileContents.find(testMessage), std::string::npos);  // The message should be in the file
}

// Test for logging to the database
TEST(LoggerTest, LogsToDatabase) {

    // Create a Logger instance with a test message
    std::string testMessage = "Database log test message";
    Logger logger(testMessage);

    // Check if the database has been created
    EXPECT_TRUE(fileExists("database/logs.sqlite"));

    // Check if the message has been logged to the database
    sqlite3* db;
    int rc = sqlite3_open("database/logs.sqlite", &db);
    ASSERT_EQ(rc, SQLITE_OK);

    // Prepare a query to check the logged message in the database
    std::string query = "SELECT message FROM logs WHERE message = ?";
    sqlite3_stmt* stmt;
    rc = sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr);
    ASSERT_EQ(rc, SQLITE_OK);

    sqlite3_bind_text(stmt, 1, testMessage.c_str(), -1, SQLITE_STATIC);

    // Check if the query returns a row
    rc = sqlite3_step(stmt);
    EXPECT_EQ(rc, SQLITE_ROW);  // It should return a row if the message was logged

    std::string retrievedMessage = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
    EXPECT_EQ(retrievedMessage, testMessage);  // Verify that the message matches

    // Finalize the query and close the database
    sqlite3_finalize(stmt);
    sqlite3_close(db);
}
