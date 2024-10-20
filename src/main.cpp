#include "LogisticRegression.h"
#include "DatabaseOperations.h"
#include "Logger.h"

int main() {
    // Settings for gradient descent
    double alpha = 0.000001;
    int iterations = 1000000;
    int k_folds = 5;  // Number of folds for cross-validation
    
    // Database initialization
    sqlite3* db1;
    sqlite3* db2;
    DatabaseOperations db_train("database/trening_data.sqlite", &db1);
    DatabaseOperations db_test("database/test_data.sqlite", &db2);
    
    if (!db_train.open_database() || !db_test.open_database()) {
        Logger log("Failed to open the database");
        std::cerr << "Error: Unable to open the database!" << std::endl;
        return -1;
    } else {
        std::cout << "Database opened successfully." << std::endl;
    }
    
    LogisticRegression model(alpha, iterations);
    
    // Perform cross-validation on k folds
    model.crossValidation(db_train, k_folds);
    
    // Train and test the model
    model.trainModel(db_train, db_test);

    return 0;
}
