#include "task-2.h"
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>

std::vector<DataPoint> gradient_dataset;
std::vector<DataPoint> gradient_predictions;

std::vector<DataPoints> gradient_dataset_multi;
std::vector<DataPoints> gradient_predictions_multi;

std::vector<DataPoint>loadDatasetSingle(const std::string& filename) {
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

std::vector<DataPoints> loadDatasetMulti(const std::string& filename) {
    std::vector<DataPoints> dataset;
    std::ifstream inFile(filename);
    if (!inFile) {
        throw std::runtime_error("Could not open file: " + filename);
    }
    std::string line;
    std::getline(inFile, line); // Skip header
    while (std::getline(inFile, line)) {
        std::istringstream iss(line);
        std::string x1_str, x2_str, y_str;
        if (std::getline(iss, x1_str, ',') && std::getline(iss, x2_str, ',') && std::getline(iss, y_str)) {
            double x1 = std::stod(x1_str);
            double x2 = std::stod(x2_str);
            double y = std::stod(y_str);
            dataset.push_back({x1, x2, y});
        }
    }
    inFile.close();
    return dataset;
}

GradientRegression::GradientRegression(double learning_rate, int num_epochs, std::string datasetFilename)
    : omega(0.0), beta(0.0), eta(learning_rate), epochs(num_epochs), datasetFilename(datasetFilename) {
    gradient_dataset = loadDatasetSingle(datasetFilename);
}

std::vector<DataPoint> GradientRegression::predict(const std::vector<DataPoint>& dataset) {
    std::vector<DataPoint> predictions;
    for (const auto& point : dataset) {
        double y_pred = beta + omega * point.x;
        gradient_predictions.push_back({point.x, y_pred});
    }
    return predictions;
}

double GradientRegression::compute_loss(const std::vector<DataPoint>& predictions, const std::vector<DataPoint>& dataset) {
    double total_loss = 0.0;
    for (long i = 0; i < dataset.size(); ++i) {
        double diff = predictions[i].y - dataset[i].y;
        total_loss += diff * diff;
    }
    return total_loss / (dataset.size() * 2);
}

double GradientRegression::compute_omega_gradient(const std::vector<DataPoint>& predictions, const std::vector<DataPoint>& dataset) {
    double gradient = 0.0;
    for (long i = 0; i < dataset.size(); ++i) {
        gradient += (predictions[i].y - dataset[i].y) * dataset[i].x;
    }
    return gradient / dataset.size();
}

double GradientRegression::compute_beta_gradient(const std::vector<DataPoint>& predictions, const std::vector<DataPoint>& dataset) {
    double gradient = 0.0;
    for (long i = 0; i < dataset.size(); ++i) {
        gradient += predictions[i].y - dataset[i].y;
    }
    return gradient / dataset.size();
}

void GradientRegression::update_parameters() {
    double omega_gradient = compute_omega_gradient(gradient_predictions, gradient_dataset);
    double beta_gradient = compute_beta_gradient(gradient_predictions, gradient_dataset);

    omega -= eta * omega_gradient;
    beta -= eta * beta_gradient;
}

MultiGradientRegression::MultiGradientRegression(double learning_rate, int num_epochs, std::string datasetFilename)
    : omegas(2, 0.0), beta(0.0), eta(learning_rate), epochs(num_epochs), datasetFilename(datasetFilename)    {
    gradient_dataset_multi = loadDatasetMulti(datasetFilename);
}

std::vector<DataPoints> MultiGradientRegression::predict(const std::vector<DataPoints>& dataset) {
    std::vector<DataPoints> predictions;
    for (const auto& point : dataset) {
        double x1_pred = beta + omegas[0] * point.x1;
        double x2_pred = beta + omegas[1] * point.x2;
        predictions.push_back({point.y, x1_pred, x2_pred});
    }
    return predictions;
}

double MultiGradientRegression::compute_loss(const std::vector<DataPoints>& predictions, const std::vector<DataPoints>& dataset) {
    double total_loss = 0.0;
    for (long i = 0; i < dataset.size(); ++i) {
        double diff_x1 = predictions[i].x1 - dataset[i].x1;
        double diff_x2 = predictions[i].x2 - dataset[i].x2;
        total_loss += (diff_x1 * diff_x1 + diff_x2 * diff_x2) / 2.0;
    }
    return total_loss / dataset.size();
}

void MultiGradientRegression::update__multi_parameters() {
    double omega_gradient_x1 = 0.0;
    double omega_gradient_x2 = 0.0;
    double beta_gradient = 0.0;

    for (long i = 0; i < gradient_dataset_multi.size(); ++i) {
        double diff_x1 = gradient_predictions_multi[i].x1 - gradient_dataset_multi[i].x1;
        double diff_x2 = gradient_predictions_multi[i].x2 - gradient_dataset_multi[i].x2;

        omega_gradient_x1 += diff_x1 * gradient_dataset_multi[i].x1;
        omega_gradient_x2 += diff_x2 * gradient_dataset_multi[i].x2;
        beta_gradient += diff_x1 + diff_x2;
    }

    omega_gradient_x1 /= gradient_dataset_multi.size();
    omega_gradient_x2 /= gradient_dataset_multi.size();
    beta_gradient /= (gradient_dataset_multi.size() * 2);

    omegas[0] -= eta * omega_gradient_x1;
    omegas[1] -= eta * omega_gradient_x2;
    beta -= eta * beta_gradient;
}