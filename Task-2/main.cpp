#include "task-2.h"
#include <iostream>
#include <vector>
#include <cmath>
#include <cassert>

int numPoints = 100;
double trueOmega = 2.0;
double trueBeta = 1.0;
double noiseLevel = 0.5;
double testTolerance = 0.5;
double learningRate = 0.0001;
int numEpochs = 5000;

void test_gradient_regression() {
    std::cout << "Starting Gradient Regression Test..." << std::endl;

    GradientRegression model(learningRate, numEpochs, "data.csv");

    gradient_predictions.clear();
    model.predict(gradient_dataset);
    const double initial_loss = model.compute_loss(gradient_predictions, gradient_dataset);

    for (int epoch = 0; epoch < numEpochs; ++epoch) {
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
    std::cout << "Learned Omega: " << model.omega << std::endl;
    std::cout << "Learned Beta: " << model.beta << std::endl;
    if (std::abs(model.omega - trueOmega) < testTolerance && std::abs(model.beta - trueBeta) < testTolerance) {
        std::cout << "Test Passed: Parameters are close to true values." << std::endl;
    } else {
        std::cerr << "Test Failed: Parameters are not close to true values." << std::endl;
    }
}

void test_multi_regression() {
    std::cout << "Starting Multi-Regression Test..." << std::endl;

    MultiGradientRegression model(learningRate, numEpochs, "data_multi.csv");

    gradient_predictions_multi = model.predict(gradient_dataset_multi);
    const double initial_loss = model.compute_loss(gradient_predictions_multi, gradient_dataset_multi);

    for (int epoch = 0; epoch < numEpochs; ++epoch) {
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
    if (model.omegas[0] > 0 && model.omegas[1] > 0 && model.beta > 0) {
        std::cout << "Test Passed: Multi-parameters are positive." << std::endl;
    } else {
        std::cerr << "Test Failed: Multi-parameters are not positive." << std::endl;
    }
}

int main() {
    generateDataset(numPoints, trueOmega, trueBeta, noiseLevel);
    test_gradient_regression();
    return 0;
}

