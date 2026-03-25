#include "task-2.h"
#include <iostream>
#include <vector>
#include <cmath>
#include <cassert>

void test_regression() {
    std::cout << "Starting Regression Test..." << std::endl;

    // Note: generateDataset is defined in gradient-regression.cpp
    double true_omega = 3.0; // Slope
    double true_beta = 2.0;  // Intercept
    double noise_std = 0.5;  // Low noise for testing convergence
    int num_points = 100;

    dataset = generateDataset(num_points, true_omega, true_beta, noise_std);

    omega = 0.0; // Start with 0 slope
    beta = 0.0;  // Start with 0 intercept
    eta = 0.01;  // Learning rate
    epochs = 20000; // Sufficient epochs for convergence
    double initial_loss = 0.0;
    
    predictions = predict(dataset);
    initial_loss = compute_loss(predictions, dataset);
    std::cout << "Initial Parameters: omega=" << omega << ", beta=" << beta << std::endl;
    std::cout << "Initial Loss: " << initial_loss << std::endl;

    for (int epoch = 0; epoch < epochs; ++epoch) {
        predictions = predict(dataset); // Update predictions based on current omega/beta
        update_parameters();            // Update omega/beta based on predictions vs dataset
    }

    // Final prediction & loss
    predictions = predict(dataset);
    double final_loss = compute_loss(predictions, dataset);

    std::cout << "Final Parameters: omega=" << omega << ", beta=" << beta << std::endl;
    std::cout << "Final Loss: " << final_loss << std::endl;
    // Check if loss decreased
    if (dataset.size() > 0 && final_loss >= initial_loss) {
        std::cerr << "Test Failed: Loss did not decrease." << std::endl;
    } else {
        std::cout << "Test Passed: Loss decreased." << std::endl;
    }
    // Check if parameters are close to true values (within tolerance)
    double tolerance = 0.5; // Allow some deviation due to noise
    if (std::abs(omega - true_omega) < tolerance && std::abs(beta - true_beta) < tolerance) {
        std::cout << "Test Passed: Parameters converged to true values." << std::endl;
    } else {
        std::cerr << "Test Failed: Parameters did not converge close enough. Expected omega=" << true_omega << ", beta=" << true_beta << std::endl;
    }
}

int main() {
    test_regression();
    return 0;
}

