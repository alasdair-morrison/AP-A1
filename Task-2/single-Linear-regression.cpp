#include "task-2.h"
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>


// Load dataset 


std::vector<DataPoint> loadDatasetSingle(const std::string& filename) {
    std::vector<DataPoint> dataset;
    std::ifstream inFile(filename);

    if (!inFile) {
        throw std::runtime_error("Could not open file: " + filename);
    }

    std::string line;
    std::getline(inFile, line); // Skip header

    while (std::getline(inFile, line)) {
        std::istringstream iss(line);
        std::string x_str, y_str;

        if (std::getline(iss, x_str, ',') && std::getline(iss, y_str)) {
            double x = std::stod(x_str);
            double y = std::stod(y_str);
            dataset.push_back({x, y});
        }
    }

    inFile.close();
    return dataset;
}


// NORMAL EQUATION IMPLEMENTATION

// Compute slope (omega) and intercept (beta)
// directly using the normal equation for simple linear regression.
void computeNormalEquation(const std::vector<DataPoint>& dataset, double& omega, double& beta) {

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