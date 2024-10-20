#include <gtest/gtest.h>
#include "LogisticRegression.h"
#include "DatabaseOperations.h"
#include <vector>
#include <tuple>
#include <cmath>

class MockDatabaseOperations : public DatabaseOperations {
public:
    MockDatabaseOperations(const std::vector<std::tuple<int, int, int, int, int, int, int, int, int, double, int, int, int, int>>& rows)
        : DatabaseOperations("", nullptr), rows(rows), current_row(0) {}

    std::optional<std::tuple<int, int, int, int, int, int, int, int, int, double, int, int, int, int>> fetch_row(int row_number) override {
        if (row_number >= 0 && row_number < rows.size()) {
            return rows[row_number];
        }
        return std::nullopt;
    }

    void reset() {
        current_row = 0;
    }

private:
    std::vector<std::tuple<int, int, int, int, int, int, int, int, int, double, int, int, int, int>> rows;
    int current_row;
};

// Testing the `trainModel` function
TEST(LogisticRegressionTest, TrainModelTest) {
    // Sample training and test data
    std::vector<std::tuple<int, int, int, int, int, int, int, int, int, double, int, int, int, int>> training_data = {
        {45, 1, 3, 120, 240, 0, 1, 150, 0, 2.0, 1, 0, 2, 1}, // expected target = 1
        {34, 0, 2, 130, 220, 1, 0, 140, 1, 1.5, 0, 1, 1, 0}, // expected target = 0
    };
    
    std::vector<std::tuple<int, int, int, int, int, int, int, int, int, double, int, int, int, int>> test_data = {
        {50, 1, 4, 135, 250, 1, 1, 160, 0, 3.0, 1, 0, 2, 1}, // expected target = 1
        {28, 0, 1, 110, 200, 0, 0, 120, 1, 1.0, 0, 1, 1, 0}, // expected target = 0
    };

    // Mocking database objects
    MockDatabaseOperations db_train(training_data);
    MockDatabaseOperations db_test(test_data);

    // Creating a model instance
    LogisticRegression model(0.01, 1000);

    // Training the model
    model.trainModel(db_train, db_test);
}

// Testing the `crossValidation` function
TEST(LogisticRegressionTest, CrossValidationTest) {
    // Sample data
    std::vector<std::tuple<int, int, int, int, int, int, int, int, int, double, int, int, int, int>> data = {
        {45, 1, 3, 120, 240, 0, 1, 150, 0, 2.0, 1, 0, 2, 1}, // expected target = 1
        {34, 0, 2, 130, 220, 1, 0, 140, 1, 1.5, 0, 1, 1, 0}, // expected target = 0
        {50, 1, 4, 135, 250, 1, 1, 160, 0, 3.0, 1, 0, 2, 1}, // expected target = 1
        {28, 0, 1, 110, 200, 0, 0, 120, 1, 1.0, 0, 1, 1, 0}, // expected target = 0
    };

    // Mocking the database object
    MockDatabaseOperations db_ops(data);

    // Creating a model instance
    LogisticRegression model(0.01, 1000);

    // Cross-validation
    model.crossValidation(db_ops, 2); // k=2 folds
}
