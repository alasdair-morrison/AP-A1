#include "task-2.h"
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>


// Load dataset 



// NORMAL EQUATION IMPLEMENTATION

// Compute slope (omega) and intercept (beta)
// directly using the normal equation for simple linear regression.
void NormalRegression::computeNormalEquation(const std::vector<DataPoint>& dataset) {

    if (dataset.empty()) {
        throw std::runtime_error("Dataset is empty.");
    }

    double sum_x = 0.0;
    double sum_y = 0.0;
    double sum_xy = 0.0;
    double sum_xx = 0.0;

    long m = dataset.size();

    // Compute required sums
    for (const auto& point : dataset) {
        sum_x += point.x;
        sum_y += point.y;
        sum_xy += point.x * point.y;
        sum_xx += point.x * point.x;
    }

    double denominator = m * sum_xx - sum_x * sum_x;

    if (denominator == 0.0) {
        throw std::runtime_error("Cannot compute normal equation (division by zero).");
    }

    // Apply normal equation formulas
    omega = (m * sum_xy - sum_x * sum_y) / denominator;
    beta = (sum_y - omega * sum_x) / m;
}



// Prediction Function


// Use computed omega and beta to predict y values
std::vector<DataPoint> predictNormalEquation(const std::vector<DataPoint>& dataset, double omega, double beta) {

    std::vector<DataPoint> predictions;

    for (const auto& point : dataset) {
        double y_pred = beta + omega * point.x;
        predictions.push_back({point.x, y_pred});
    }

    return predictions;
}