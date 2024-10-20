#ifndef LOGISTICREGRESSION_H
#define LOGISTICREGRESSION_H

#include "DatabaseOperations.h"
#include <vector>
#include <tuple>

class LogisticRegression {
private:
    std::vector<double> theta;
    double alpha;
    int iterations;

    // Helper functions
    double sigmoid(double z);
    double computeCostSingle(const std::tuple<int, int, int, int, int, int, int, int, int, double, int, int, int, int>& row);
    void gradientDescentStep(const std::tuple<int, int, int, int, int, int, int, int, int, double, int, int, int, int>& row);
    int calculateErrors(const std::vector<std::tuple<int, int, int, int, int, int, int, int, int, double, int, int, int, int>>& test_data);

public:
    LogisticRegression(double alpha, int iterations);

    void crossValidation(DatabaseOperations& db_ops, int k_folds);
    void trainModel(DatabaseOperations& db_train, DatabaseOperations& db_test);
};

#endif // LOGISTICREGRESSION_H
