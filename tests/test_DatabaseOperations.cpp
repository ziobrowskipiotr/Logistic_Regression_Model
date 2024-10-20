#include <gtest/gtest.h>
#include "DatabaseOperations.h"
#include <vector>

// Structure to store information about databases and expected results
struct TestDatabase {
    std::string db_name;
    bool should_open;
    bool should_have_valid_schema;
    bool should_fetch_data;
};

// Test with a loop for multiple databases
// DatabaseOperationsTest - name of the test, MultipleDatabaseTest - name of the functionality being tested
TEST(DatabaseOperationsTest, MultipleDatabaseTest) {
    // List of databases and expected results
    std::vector<TestDatabase> databases = {
        {"tests/test_db/non_existent.sqlite", false, false, false},  // Database does not exist
        {"tests/test_db/empty_test.sqlite", true, false, false},     // Empty database
        {"tests/test_db/valid_test.sqlite", true, true, true}        // Valid database with data
    };

    for (const auto& test_db : databases) {
        sqlite3* db = nullptr;
        DatabaseOperations dbOps(test_db.db_name, &db);

        // Test opening the database
        bool opened = dbOps.open_database();
        EXPECT_EQ(opened, test_db.should_open) << "Test for database: " << test_db.db_name;

        if (opened) {
            // Test table schema verification if the database is opened
            bool schema_valid = dbOps.verify_table_schema();
            EXPECT_EQ(schema_valid, test_db.should_have_valid_schema) << "Test for database: " << test_db.db_name;

            // If the schema is valid and data is expected, try to fetch a row
            if (test_db.should_have_valid_schema && test_db.should_fetch_data) {
                auto row = dbOps.fetch_row(0);
                EXPECT_TRUE(row.has_value()) << "Test for database: " << test_db.db_name;
            } else {
                // If no data is expected in the database, there should be no rows
                auto row = dbOps.fetch_row(0);
                EXPECT_FALSE(row.has_value()) << "Test for database: " << test_db.db_name;
            }

            // Close the database
            dbOps.close_database();
        }
    }
}
