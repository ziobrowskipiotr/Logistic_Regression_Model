#ifndef DATABASEOPERATIONS_H
#define DATABASEOPERATIONS_H

#include <sqlite3.h>
#include <iostream>
#include <tuple>
#include <optional>  // For std::optional
#include "Logger.h"

class DatabaseOperations {
private:
    std::string dbName;
    sqlite3** db;  // Pointer to SQLite database

public:
    // Constructor
    DatabaseOperations(std::string dbName, sqlite3** db);

    // Opens the database and returns true if successful
    bool open_database();

    // Closes the database
    void close_database();

    // Fetches a row from the database as a tuple (optional return)
    virtual std::optional<std::tuple<int, int, int, int, int, int, int, int, int, double, int, int, int, int>> fetch_row(int row_number);

    bool DatabaseOperations::verify_table_schema();

    // Destructor to close the database
    ~DatabaseOperations();
};

#endif // DATABASEOPERATIONS_H
