#include "task-2.h"
#include <vector>
#include <iostream>
#include <random> // Required for modern C++ random number generation

double omega = 0.01; // Learning rate
double beta = 0.0; // Initial bias
double eta = 0.01; // Learning rate for gradient descent
int epochs = 1000; // Number of iterations for training


std::vector<DataPoint> dataset;
std::vector<DataPoint> predictions;

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

std::vector<DataPoint> generateDataset(int num_points, double k, double m, double noise_level) {
    std::vector<DataPoint> dataset;
    
    // 1. Initialize the Random Number Generator
    std::random_device rd;  // Obtains a true random seed from your hardware
    std::mt19937 gen(rd()); // The standard Mersenne Twister engine seeded by rd()
    
    // 2. Define our Distributions
    // We want our base 'x' values to be spread out uniformly, say between 0.0 and 10.0
    std::uniform_real_distribution<double> x_dist(0.0, 10.0); 
    
    // We want our noise to be Gaussian (Normal distribution) centered at 0
    std::normal_distribution<double> noise_dist(0.0, noise_level);

    // 3. Generate the Data Points
    for (int i = 0; i < num_points; ++i) {
        // Step 1: Generate base x and calculate exact y = k*x + m
        double x_exact = x_dist(gen);
        double y_exact = k * x_exact + m;
        
        // Step 2: Add noise to BOTH x and y (as explicitly requested in the assignment)
        double x_noisy = x_exact + noise_dist(gen);
        double y_noisy = y_exact + noise_dist(gen);
        
        // Store the noisy tuple in our dataset
        dataset.push_back({x_noisy, y_noisy});
    }
    
    return dataset;
}

void run() {
    // Generate 100 points for the line y = 3x + 4, with a noise standard deviation of 0.5
    dataset = generateDataset(100, 3.0, 4.0, 0.5);
    predictions = predict(dataset);
    double loss = compute_loss(predictions, dataset);
    std::cout << "Initial Loss: " << loss << std::endl;
}
