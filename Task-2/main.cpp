#include "task-2.h"
#include <iostream>
#include <vector>
#include <cmath>
#include <cassert>

void test_gradient_regression() {
    std::cout << "Starting Gradient Regression Test..." << std::endl;

    GradientRegression model(0.0001, 5000, "data.csv");

    gradient_predictions.clear();
    model.predict(gradient_dataset);
    const double initial_loss = model.compute_loss(gradient_predictions, gradient_dataset);

    for (int epoch = 0; epoch < 5000; ++epoch) {
        gradient_predictions.clear();
        model.predict(gradient_dataset);
        model.update_parameters();
    }

    gradient_predictions.clear();
    model.predict(gradient_dataset);
    const double final_loss = model.compute_loss(gradient_predictions, gradient_dataset);

    std::cout << "Initial Loss: " << initial_loss << std::endl;
    std::cout << "Final Loss: " << final_loss << std::endl;
    if (!gradient_dataset.empty() && final_loss < initial_loss) {
        std::cout << "Test Passed: Loss decreased." << std::endl;
    } else {
        std::cerr << "Test Failed: Loss did not decrease." << std::endl;
    }
}

void test_multi_regression() {
    std::cout << "Starting Multi-Regression Test..." << std::endl;

    MultiGradientRegression model(0.0001, 5000, "data_multi.csv");

    gradient_predictions_multi = model.predict(gradient_dataset_multi);
    const double initial_loss = model.compute_loss(gradient_predictions_multi, gradient_dataset_multi);

    for (int epoch = 0; epoch < 5000; ++epoch) {
        gradient_predictions_multi = model.predict(gradient_dataset_multi);
        model.update__multi_parameters();
    }

    gradient_predictions_multi = model.predict(gradient_dataset_multi);
    const double final_loss = model.compute_loss(gradient_predictions_multi, gradient_dataset_multi);

    std::cout << "Initial Loss: " << initial_loss << std::endl;
    std::cout << "Final Loss: " << final_loss << std::endl;
    if (!gradient_dataset_multi.empty() && final_loss < initial_loss) {
        std::cout << "Test Passed: Multi-loss decreased." << std::endl;
    } else {
        std::cerr << "Test Failed: Multi-loss did not decrease." << std::endl;
    }
}

int main() {
    test_gradient_regression();
    return 0;
}

