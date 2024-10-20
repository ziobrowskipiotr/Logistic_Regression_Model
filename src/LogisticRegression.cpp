#include "LogisticRegression.h"
#include <iostream>
#include <cmath>
#include <algorithm>  // std::random_shuffle
#include <ctime>      // std::time
#include <random>     // std::default_random_engine

LogisticRegression::LogisticRegression(double alpha, int iterations)
    : alpha(alpha), iterations(iterations) {
    theta.resize(13, 0.0);  // Number of coefficients (features + bias)
}

double LogisticRegression::sigmoid(double z) {
    return 1.0 / (1.0 + exp(-z));
}

double LogisticRegression::computeCostSingle(const std::tuple<int, int, int, int, int, int, int, int, int, double, int, int, int, int>& row) {
    double z = theta[0];  // Bias
    z += std::get<0>(row) * theta[1];
    z += std::get<1>(row) * theta[2];
    z += std::get<2>(row) * theta[3];
    z += std::get<3>(row) * theta[4];
    z += std::get<4>(row) * theta[5];
    z += std::get<5>(row) * theta[6];
    z += std::get<6>(row) * theta[7];
    z += std::get<7>(row) * theta[8];
    z += std::get<8>(row) * theta[9];
    z += std::get<10>(row) * theta[10];
    z += std::get<11>(row) * theta[11];
    z += std::get<12>(row) * theta[12];

    double h = sigmoid(z);
    double y = std::get<13>(row);
    return -y * log(h) - (1 - y) * log(1 - h);
}

void LogisticRegression::gradientDescentStep(const std::tuple<int, int, int, int, int, int, int, int, int, double, int, int, int, int>& row) {
    double z = theta[0];
    z += std::get<0>(row) * theta[1];
    z += std::get<1>(row) * theta[2];
    z += std::get<2>(row) * theta[3];
    z += std::get<3>(row) * theta[4];
    z += std::get<4>(row) * theta[5];
    z += std::get<5>(row) * theta[6];
    z += std::get<6>(row) * theta[7];
    z += std::get<7>(row) * theta[8];
    z += std::get<8>(row) * theta[9];
    z += std::get<10>(row) * theta[10];
    z += std::get<11>(row) * theta[11];
    z += std::get<12>(row) * theta[12];

    double h = sigmoid(z);
    double y = std::get<13>(row);
    double error = h - y;

    theta[0] -= alpha * error;
    theta[1] -= alpha * error * std::get<0>(row);
    theta[2] -= alpha * error * std::get<1>(row);
    theta[3] -= alpha * error * std::get<2>(row);
    theta[4] -= alpha * error * std::get<3>(row);
    theta[5] -= alpha * error * std::get<4>(row);
    theta[6] -= alpha * error * std::get<5>(row);
    theta[7] -= alpha * error * std::get<6>(row);
    theta[8] -= alpha * error * std::get<7>(row);
    theta[9] -= alpha * error * std::get<8>(row);
    theta[10] -= alpha * error * std::get<10>(row);
    theta[11] -= alpha * error * std::get<11>(row);
    theta[12] -= alpha * error * std::get<12>(row);
}

void LogisticRegression::crossValidation(DatabaseOperations& db_ops, int k_folds) {
    std::vector<double> accuracy;
    std::vector<std::tuple<int, int, int, int, int, int, int, int, int, double, int, int, int, int>> all_rows;
    int row_number = 0;
    auto row = db_ops.fetch_row(row_number);
    
    while (row.has_value()) {
        all_rows.push_back(row.value());
        row_number++;
        row = db_ops.fetch_row(row_number);
    }

    std::shuffle(all_rows.begin(), all_rows.end(), std::default_random_engine(std::time(0)));
    int fold_size = all_rows.size() / k_folds;

    for (int fold = 0; fold < k_folds; ++fold) {
        std::vector<std::tuple<int, int, int, int, int, int, int, int, int, double, int, int, int, int>> train_data, test_data;
        for (int i = 0; i < all_rows.size(); ++i) {
            if (i >= fold * fold_size && i < (fold + 1) * fold_size) {
                test_data.push_back(all_rows[i]);
            } else {
                train_data.push_back(all_rows[i]);
            }
        }

        for (int iter = 0; iter < iterations; ++iter) {
            for (const auto& row : train_data) {
                gradientDescentStep(row);
            }
        }

        int correct_predictions = 0;
        int total_predictions = 0;
        for (const auto& row : test_data) {
            double z = theta[0];
            z += std::get<0>(row) * theta[1];
            z += std::get<1>(row) * theta[2];
            z += std::get<2>(row) * theta[3];
            z += std::get<3>(row) * theta[4];
            z += std::get<4>(row) * theta[5];
            z += std::get<5>(row) * theta[6];
            z += std::get<6>(row) * theta[7];
            z += std::get<7>(row) * theta[8];
            z += std::get<8>(row) * theta[9];
            z += std::get<10>(row) * theta[10];
            z += std::get<11>(row) * theta[11];
            z += std::get<12>(row) * theta[12];

            double h = sigmoid(z);
            int prediction = h >= 0.5 ? 1 : 0;
            int actual = std::get<13>(row);

            if (prediction == actual) {
                correct_predictions++;
            }
            total_predictions++;
        }
        accuracy.push_back(static_cast<double>(correct_predictions) / total_predictions);
        std::cout << "Accuracy for fold " << (fold + 1) << ": " << accuracy.back() << std::endl;
    }
    double mean_accuracy = 0.0;
    for (double acc : accuracy) {
        mean_accuracy += acc;
    }
    mean_accuracy /= accuracy.size();
    std::cout << "Mean accuracy for validation: " << mean_accuracy << "\n" << std::endl;
}

void LogisticRegression::trainModel(DatabaseOperations& db_train, DatabaseOperations& db_test) {
    std::vector<std::tuple<int, int, int, int, int, int, int, int, int, double, int, int, int, int>> train_data, test_data;
    
    int row_number_train = 0;
    auto row = db_train.fetch_row(row_number_train);
    while (row.has_value()) {
        train_data.push_back(row.value());
        row_number_train++;
        row = db_train.fetch_row(row_number_train);
    }

    int row_number_test = 0;
    row = db_test.fetch_row(row_number_test);
    while (row.has_value()) {
        test_data.push_back(row.value());
        row_number_test++;
        row = db_test.fetch_row(row_number_test);
    }

    for (int iter = 0; iter < iterations; ++iter) {
        for (const auto& row : train_data) {
            gradientDescentStep(row);
        }
    }

    int correct_predictions = 0;
    int total_predictions = 0;
    for (const auto& row : test_data) {
        double z = theta[0];
        z += std::get<0>(row) * theta[1];
        z += std::get<1>(row) * theta[2];
        z += std::get<2>(row) * theta[3];
        z += std::get<3>(row) * theta[4];
        z += std::get<4>(row) * theta[5];
        z += std::get<5>(row) * theta[6];
        z += std::get<6>(row) * theta[7];
        z += std::get<7>(row) * theta[8];
        z += std::get<8>(row) * theta[9];
        z += std::get<10>(row) * theta[10];
        z += std::get<11>(row) * theta[11];
        z += std::get<12>(row) * theta[12];

        double h = sigmoid(z);
        int prediction = h >= 0.5 ? 1 : 0;
        int actual = std::get<13>(row);

        if (prediction == actual) {
            correct_predictions++;
        }
        total_predictions++;
    }
    double accuracy = static_cast<double>(correct_predictions) / total_predictions;
    std::cout << "Model accuracy: " << accuracy << std::endl;
}
