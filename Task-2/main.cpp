#include "task-2.h"
#include <iostream>
#include <vector>
#include <cmath>
#include <cassert>
#include <string>
#include <sstream>

int numPoints = 100;
double trueOmega = 2.0;
double trueBeta = 1.0;
double noiseLevel = 0.5;
double testTolerance = 0.5;
double learningRate = 0.0001;
int numEpochs = 30000;

template <typename T>
T readValueOrDefault(const std::string& prompt, T defaultValue) {
    std::cout << prompt << " [default: " << defaultValue << "]: ";
    std::string line;
    std::getline(std::cin, line);

    if (line.empty()) {
        return defaultValue;
    }

    std::stringstream ss(line);
    T value;
    if (ss >> value && ss.eof()) {
        return value;
    }

    std::cout << "Invalid input. Using default value: " << defaultValue << std::endl;
    return defaultValue;
}

void configureRunParametersFromConsole() {
    std::cout << "Configure run parameters (press Enter to keep defaults)" << std::endl;
    trueOmega = readValueOrDefault<double>("trueOmega", trueOmega);
    trueBeta = readValueOrDefault<double>("trueBeta", trueBeta);
    noiseLevel = readValueOrDefault<double>("noiseLevel", noiseLevel);
    numEpochs = readValueOrDefault<int>("number of epochs", numEpochs);
    learningRate = readValueOrDefault<double>("learning rate", learningRate);
}

/*void test_normal_regression() {
    std::cout << "Starting Normal Regression Test..." << std::endl;

    NormalRegression model;

    gradient_predictions.clear();
    gradient_predictions = model.predict(gradient_dataset);
    //const double initial_loss = model.compute_loss(gradient_predictions, gradient_dataset);

    //std::cout << "Initial Loss: " << initial_loss << std::endl;
    std::cout << "Learned Omega: " << model.get_omega() << std::endl;
    std::cout << "Learned Beta: " << model.get_beta() << std::endl;
    if (std::abs(model.get_omega() - trueOmega) < testTolerance && std::abs(model.get_beta() - trueBeta) < testTolerance) {
        std::cout << "Test Passed: Parameters are close to true values." << std::endl;
    } else {
        std::cerr << "Test Failed: Parameters are not close to true values." << std::endl;
    }
}*/

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

    MultiGradientRegression model(learningRate, numEpochs, "dataMulti.csv");

    gradient_predictions_multi.clear();
    model.predict(gradient_dataset_multi);
    const double initial_loss = model.compute_loss(gradient_predictions_multi, gradient_dataset_multi);

    for (int epoch = 0; epoch < numEpochs; ++epoch) {
        gradient_predictions_multi.clear();
        model.predict(gradient_dataset_multi);
        model.update__multi_parameters();
    }

    gradient_predictions_multi.clear();
    model.predict(gradient_dataset_multi);
    const double final_loss = model.compute_loss(gradient_predictions_multi, gradient_dataset_multi);

    std::cout << "Initial Loss: " << initial_loss << std::endl;
    std::cout << "Final Loss: " << final_loss << std::endl;
    if (!gradient_dataset_multi.empty() && final_loss < initial_loss) {
        std::cout << "Test Passed: Multi-loss decreased." << std::endl;
    } else {
        std::cerr << "Test Failed: Multi-loss did not decrease." << std::endl;
    }
    std::cout << "Learned Omegas: " << model.omegas[0] << ", " << model.omegas[1] << std::endl;
    std::cout << "Learned Beta: " << model.beta << std::endl;
    if (std::abs(model.omegas[0] - trueOmega) < testTolerance && std::abs(model.omegas[1] - trueOmega) < testTolerance && std::abs(model.beta - trueBeta) < testTolerance) {
        std::cout << "Test Passed: Multi-parameters are close to true values." << std::endl;
    } else {
        std::cerr << "Test Failed: Multi-parameters are not close to true values." << std::endl;
    }
}

int main() {
    configureRunParametersFromConsole();
    generateDataset(numPoints, trueOmega, trueBeta, noiseLevel);
    generateMultiDataset(numPoints, trueOmega, trueBeta, noiseLevel);
    test_gradient_regression();
    test_multi_regression();
    return 0;
}

