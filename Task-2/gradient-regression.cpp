#include "task-2.h"
#include <vector>
#include <iostream>
#include <random> // Required for modern C++ random number generation

double omega = 0.01; // Learning rate
std::vector<double> omegas = {0.01, 0.01}; // Learning rate for second prediction (if needed)
double beta = 0.0; // Initial bias
double eta = 0.01; // Learning rate for gradient descent
int epochs = 1000; // Number of iterations for training


std::vector<DataPoint> dataset;
std::vector<DataPoint> predictions;

std::vector<DataPoints> dataset_multi;
std::vector<DataPoints> predictions_multi;

std::vector<DataPoint> load_data() {
    // Placeholder for loading data, replace with actual data loading logic
    return {{1.0, 2.0}, {2.0, 3.0}, {3.0, 5.0}};
}

std::vector<DataPoint> predict(const std::vector<DataPoint>& dataset) {
    std::vector<DataPoint> preds;
    for (const auto& point : dataset) {
        preds.push_back({point.x, beta + omega * point.x});
    }
    return preds;
}

double compute_loss(const std::vector<DataPoint>& predictions, const std::vector<DataPoint>& dataset) {
    double total_loss = 0.0;
    for (long i = 0; i < dataset.size(); ++i) {
        double diff = predictions[i].y - dataset[i].y;
        total_loss += diff * diff;
    }
    return total_loss/(dataset.size() * 2);
}

double compute_omega_gradient(const std::vector<DataPoint>& predictions, const std::vector<DataPoint>& dataset) {
    double gradient = 0.0;
    for (long i = 0; i < dataset.size(); ++i) {
        gradient += (predictions[i].y - dataset[i].y) * dataset[i].x;
    }
    return gradient / dataset.size();
}

double compute_beta_gradient(const std::vector<DataPoint>& predictions, const std::vector<DataPoint>& dataset) {
    double gradient = 0.0;
    for (long i = 0; i < dataset.size(); ++i) {
        gradient += predictions[i].y - dataset[i].y;
    }
    return gradient / dataset.size();
}

void update_parameters() {
    double omega_gradient = compute_omega_gradient(predictions, dataset);
    double beta_gradient = compute_beta_gradient(predictions, dataset);
    
    omega -= eta * omega_gradient;
    beta -= eta * beta_gradient;
}

void run() {
    // Generate 100 points for the line y = 3x + 4, with a noise standard deviation of 0.5
    dataset = generateDataset(100, 3.0, 4.0, 0.5);
    predictions = predict(dataset);
    double loss = compute_loss(predictions, dataset);
    std::cout << "Initial Loss: " << loss << std::endl;
}

std::vector<DataPoints> predict(const std::vector<DataPoints>& dataset) {
    std::vector<DataPoints> preds;
    for (const auto& point : dataset) {
        double y1_pred = beta + omegas[0] * point.x; // Prediction for y1
        double y2_pred = beta + omegas[1] * point.x; // Prediction for y2 (same as y1 in this simple model)
        preds.push_back({point.x, y1_pred, y2_pred});
    }
    return preds;
}

double compute_loss(const std::vector<DataPoints>& predictions, const std::vector<DataPoints>& dataset) {
    double total_loss = 0.0;
    for (long i = 0; i < dataset.size(); ++i) {
        double diff_y1 = predictions[i].y1 - dataset[i].y1;
        double diff_y2 = predictions[i].y2 - dataset[i].y2;
        total_loss += (diff_y1 * diff_y1 + diff_y2 * diff_y2) / 2.0; // Average loss for both predictions
    }
    return total_loss / dataset.size();
}

void update__multi_parameters() {
    double omega_gradient_y1 = 0.0;
    double omega_gradient_y2 = 0.0;
    double beta_gradient = 0.0;

    for (long i = 0; i < dataset_multi.size(); ++i) {
        double diff_y1 = predictions_multi[i].y1 - dataset_multi[i].y1;
        double diff_y2 = predictions_multi[i].y2 - dataset_multi[i].y2;

        omega_gradient_y1 += diff_y1 * dataset_multi[i].x;
        omega_gradient_y2 += diff_y2 * dataset_multi[i].x;
        beta_gradient += diff_y1 + diff_y2; // Sum of gradients for both predictions
    }

    // Average the gradients over the dataset
    omega_gradient_y1 /= dataset_multi.size();
    omega_gradient_y2 /= dataset_multi.size();
    beta_gradient /= (dataset_multi.size() * 2); // Average over both predictions

    // Update parameters using the computed gradients
    omegas[0] -= eta * omega_gradient_y1; // Update for y1
    omegas[1] -= eta * omega_gradient_y2; // Update for y2
    beta -= eta * beta_gradient;           // Update for bias
}