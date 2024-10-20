#include "DatabaseOperations.h"
#include <vector>

// Constructor for opening the database
DatabaseOperations::DatabaseOperations(std::string dbName, sqlite3** db) {
    this->dbName = std::move(dbName);  // Unikamy niepotrzebnej kopii
    this->db = db;
}

// Opens the database connection
bool DatabaseOperations::open_database() {
    int rc = sqlite3_open_v2(dbName.c_str(), db, SQLITE_OPEN_READWRITE, nullptr);  // Opening the database
    if (rc != SQLITE_OK) {
        std::string mess = "Failed to open the database: " + dbName + ". Error: " + sqlite3_errmsg(*db);
        Logger logger(mess);  // Log the failure message
        return false;
    }
    return true;
}

// Closes the database connection
void DatabaseOperations::close_database() {
    if (db && *db) {  // Sprawdzamy, czy wskaźnik nie jest pusty
        sqlite3_close(*db);
        *db = nullptr;  // Ustawiamy wskaźnik na nullptr po zamknięciu
    }
}

// Verifies if the table schema is correct (number and names of columns)
bool DatabaseOperations::verify_table_schema() {
    if (!db || !*db) {
        std::cerr << "Error: Database is not open." << std::endl;
        return false;
    }

    std::string query = "PRAGMA table_info(tablica);";
    sqlite3_stmt* stmt;

    // Przygotowujemy zapytanie, aby pobrać informacje o kolumnach
    int rc = sqlite3_prepare_v2(*db, query.c_str(), -1, &stmt, nullptr);
    if (rc != SQLITE_OK) {
        std::cerr << "Error: Unable to prepare SQL query: " << sqlite3_errmsg(*db) << std::endl;
        return false;
    }

    // Oczekiwane nazwy kolumn
    std::vector<std::string> expected_columns = {
        "age", "sex", "cp", "trestbps", "chol", "fbs", 
        "restecg", "thalach", "exang", "oldpeak", 
        "slope", "ca", "thal", "target"
    };

    std::vector<std::string> actual_columns;
    
    // Wykonujemy zapytanie i zbieramy nazwy kolumn
    while ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
        std::string column_name = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
        actual_columns.push_back(column_name);
    }

    sqlite3_finalize(stmt);

    // Sprawdzamy, czy liczba kolumn jest zgodna
    if (actual_columns.size() != expected_columns.size()) {
        std::cerr << "Error: Incorrect number of columns in table 'tablica'. Expected: " 
                  << expected_columns.size() << ", but got: " << actual_columns.size() << std::endl;
        return false;
    }

    // Sprawdzamy, czy nazwy kolumn są zgodne
    for (size_t i = 0; i < expected_columns.size(); ++i) {
        if (actual_columns[i] != expected_columns[i]) {
            std::cerr << "Error: Column mismatch. Expected: '" << expected_columns[i] 
                      << "', but got: '" << actual_columns[i] << "' at position " << i + 1 << std::endl;
            return false;
        }
    }

    return true;
}

// Fetches a row from the database by row number
std::optional<std::tuple<int, int, int, int, int, int, int, int, int, double, int, int, int, int>> DatabaseOperations::fetch_row(int row_number) {
    if (!db || !*db) {
        std::cerr << "Error: Database is not open." << std::endl;
        return std::nullopt;
    }

    sqlite3_stmt* stmt;
    std::string query = "SELECT * FROM tablica LIMIT 1 OFFSET " + std::to_string(row_number);  // We use the table 'tablica'
    
    int rc = sqlite3_prepare_v2(*db, query.c_str(), -1, &stmt, nullptr);
    if (rc != SQLITE_OK) {
        std::cerr << "Error: Unable to prepare SQL query: " << sqlite3_errmsg(*db) << std::endl;
        return std::nullopt;
    }

    // Execute the query and fetch the row
    rc = sqlite3_step(stmt);
    if (rc == SQLITE_ROW) {
        std::tuple<int, int, int, int, int, int, int, int, int, double, int, int, int, int> row;

        // Assign values to the tuple
        std::get<0>(row) = sqlite3_column_int(stmt, 0);
        std::get<1>(row) = sqlite3_column_int(stmt, 1);
        std::get<2>(row) = sqlite3_column_int(stmt, 2);
        std::get<3>(row) = sqlite3_column_int(stmt, 3);
        std::get<4>(row) = sqlite3_column_int(stmt, 4);
        std::get<5>(row) = sqlite3_column_int(stmt, 5);
        std::get<6>(row) = sqlite3_column_int(stmt, 6);
        std::get<7>(row) = sqlite3_column_int(stmt, 7);
        std::get<8>(row) = sqlite3_column_int(stmt, 8);
        std::get<9>(row) = sqlite3_column_double(stmt, 9);  // double value
        std::get<10>(row) = sqlite3_column_int(stmt, 10);
        std::get<11>(row) = sqlite3_column_int(stmt, 11);
        std::get<12>(row) = sqlite3_column_int(stmt, 12);
        std::get<13>(row) = sqlite3_column_int(stmt, 13);

        sqlite3_finalize(stmt);
        return row;
    } else if (rc != SQLITE_DONE) {
        std::cerr << "Error fetching row number: " << row_number << " | Error: " << sqlite3_errmsg(*db) << std::endl;
    }

    sqlite3_finalize(stmt);
    return std::nullopt;
}

// Destructor to close the database
DatabaseOperations::~DatabaseOperations() {
    close_database();
}
