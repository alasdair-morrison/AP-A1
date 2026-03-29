#include "task-2.h"
#include <iostream>
#include <vector>
#include <cmath>
#include <cassert>
#include <string>
#include <sstream>
 // Global variables for data generation and model parameters
int numPoints = 100;
double trueOmega1 = 2.0;
double trueOmega2 = 0.5;
double trueBeta = 1.0;
double noiseLevel = 0.5;
double testTolerance = 0.5;
double learningRate = 0.0001;
int numEpochs = 30000;

// Function to read a value from console with a default fallback (Used for configuring parameters before running tests)
template <typename T>
T readValueOrDefault(const std::string& prompt, T defaultValue) {
    std::cout << prompt << " [default: " << defaultValue << "]: "; // Prompt user for input with default value shown
    std::string line; // Read a line of input from the console
    std::getline(std::cin, line); // If the user just presses Enter, return the default value

    if (line.empty()) { // If the input is empty,
        return defaultValue; // return the default value
    }

    std::stringstream ss(line); // Try to parse the input into the expected type
    T value; // Variable to hold the parsed value
    if (ss >> value && ss.eof()) { // If parsing is successful and there are no extra characters,
        return value; // return the parsed value
    }

    std::cout << "Invalid input. Using default value: " << defaultValue << std::endl;
    return defaultValue;
}
// Method to configure simulation parameters for single linear regression tests
void configureRunParametersFromConsole() {
    std::cout << "Configure run parameters (press Enter to keep defaults)" << std::endl;
    trueOmega1 = readValueOrDefault<double>("trueOmega", trueOmega1);
    trueBeta = readValueOrDefault<double>("trueBeta", trueBeta);
    noiseLevel = readValueOrDefault<double>("noiseLevel", noiseLevel);
    numEpochs = readValueOrDefault<int>("number of epochs", numEpochs);
    learningRate = readValueOrDefault<double>("learning rate", learningRate);
}
// Method to configure simulation parameters for multi-linear regression tests
void configureRunParametersFromConsoleMulti() {
    std::cout << "Configure run parameters (press Enter to keep defaults)" << std::endl;
    trueOmega1 = readValueOrDefault<double>("trueOmega1", trueOmega1);
    trueOmega2 = readValueOrDefault<double>("trueOmega2", trueOmega2);
    trueBeta = readValueOrDefault<double>("trueBeta", trueBeta);
    noiseLevel = readValueOrDefault<double>("noiseLevel", noiseLevel);
    numEpochs = readValueOrDefault<int>("number of epochs", numEpochs);
    learningRate = readValueOrDefault<double>("learning rate", learningRate);
}
// Test function for single linear regression using the normal equation method
void test_normal_regression() {
    std::cout << "Starting Normal Regression Test..." << std::endl;
    normal_dataset = loadDatasetSingle("data.csv"); // Load dataset from file into DataPoint vector
    normal_predictions = predictNormalEquation(normal_dataset); // Generate predictions using the normal equation method
    const double initial_loss = compute_loss(normal_predictions, normal_dataset); // Compute initial loss before training
    
    for (int i = 0; i < numEpochs; ++i) { // Iteratively compute the normal equation and update predictions for a number of epochs
        normal_predictions.clear(); // Clear previous predictions to avoid accumulation of old results
        normal_predictions = predictNormalEquation(normal_dataset); // Generate new predictions based on the current parameters
        computeNormalEquation(normal_dataset); // Update the parameters (omega and beta) using the normal equation based on the current dataset
    }
    normal_predictions.clear(); // Clear predictions again to compute final predictions after training
    normal_predictions = predictNormalEquation(normal_dataset); // Generate final predictions after training
    const double final_loss = compute_loss(normal_predictions, normal_dataset); // Compute final loss after training

    std::cout << "Initial Loss: " << initial_loss << std::endl;
    std::cout << "Final Loss: " << final_loss << std::endl;
    if (!normal_dataset.empty() && final_loss < initial_loss) { // Check if the dataset is not empty and if the final loss is less than the initial loss, indicating that the model has improved
        std::cout << "Test Passed: Loss decreased." << std::endl;
    } else {
        std::cerr << "Test Failed: Loss did not decrease." << std::endl;
    }
    std::cout << "Learned Omega: " << omega << std::endl;
    std::cout << "Learned Beta: " << beta << std::endl;
    // Check if the learned parameters (omega and beta) are close to the true values used to generate the dataset, within a specified tolerance
    if (std::abs(omega - trueOmega1) < testTolerance && std::abs(beta - trueBeta) < testTolerance) {
        std::cout << "Test Passed: Parameters are close to true values." << std::endl;
    } else {
        std::cerr << "Test Failed: Parameters are not close to true values." << std::endl;
    }
}
// Test function for single linear regression using gradient descent method
void test_gradient_regression() {
    std::cout << "Starting Gradient Regression Test..." << std::endl;
    // Create an instance of the GradientRegression class, which will handle the training process using gradient descent. 
    // The constructor takes the learning rate, number of epochs, and the dataset filename as arguments.
    GradientRegression model(learningRate, numEpochs, "data.csv");

    // Clear any existing predictions
    gradient_predictions.clear();
    // Generate initial predictions using the model's predict method, which will use the current parameters (omega and beta) to make predictions based on the input dataset.
    model.predict(gradient_dataset);
    // Compute the initial loss using the model's compute_loss method, which compares the predictions to the actual dataset and calculates a loss value (e.g., mean squared error).
    const double initial_loss = model.compute_loss(gradient_predictions, gradient_dataset);
    // Run the training loop for a specified number of epochs.
    for (int epoch = 0; epoch < numEpochs; ++epoch) {
        gradient_predictions.clear();// Clear previous predictions to prepare for the next iteration
        model.predict(gradient_dataset);// Generate new predictions based on the current parameters (omega and beta)
        model.update_parameters(); // Update the model parameters (omega and beta) using the computed predictions.
    }
    // After training is complete, clear predictions again to compute final predictions based on the updated parameters.
    gradient_predictions.clear();
    model.predict(gradient_dataset);
    // Compute the final loss after training to evaluate the performance of the model.
    const double final_loss = model.compute_loss(gradient_predictions, gradient_dataset);

    std::cout << "Initial Loss: " << initial_loss << std::endl;
    std::cout << "Final Loss: " << final_loss << std::endl;
    // Check if the dataset is not empty and if the final loss is less than the initial loss, indicating that the model has improved during training.
    if (!gradient_dataset.empty() && final_loss < initial_loss) {
        std::cout << "Test Passed: Loss decreased." << std::endl;
    } else {
        std::cerr << "Test Failed: Loss did not decrease." << std::endl;
    }
    std::cout << "Learned Omega: " << model.omega << std::endl;
    std::cout << "Learned Beta: " << model.beta << std::endl;
    // Check if the learned parameters (omega and beta) are close to the true values used to generate the dataset, within a specified tolerance.
    if (std::abs(model.omega - trueOmega1) < testTolerance && std::abs(model.beta - trueBeta) < testTolerance) {
        std::cout << "Test Passed: Parameters are close to true values." << std::endl;
    } else {
        std::cerr << "Test Failed: Parameters are not close to true values." << std::endl;
    }
}
// Test function for multi-linear regression using gradient descent method
void test_multi_regression() {
    std::cout << "Starting Multi-Regression Test..." << std::endl;
    // Create an instance of the MultiGradientRegression class, which will handle the training process for multi-linear regression using gradient descent. 
    // The constructor takes the learning rate, number of epochs, and the dataset filename as arguments
    MultiGradientRegression model(learningRate, numEpochs, "dataMulti.csv");
    // Clear any existing predictions for the multi-linear regression dataset
    gradient_predictions_multi.clear();
    // Generate initial predictions based on the current parameters
    model.predict(gradient_dataset_multi);
    // Compute the inital loss for the model
    const double initial_loss = model.compute_loss(gradient_predictions_multi, gradient_dataset_multi);

    for (int epoch = 0; epoch < numEpochs; ++epoch) { // Run the training loop for a specified number of epochs
        gradient_predictions_multi.clear(); // Clear previous predictions to prepare for the next iteration
        model.predict(gradient_dataset_multi); // Generate new predictions
        model.update_multi_parameters(); // Update model parameters using predicted values
    }
    // After training is complete, clear predictions again to compute final predictions based on the updated parameters.
    gradient_predictions_multi.clear();
    model.predict(gradient_dataset_multi);
    // Compute the final loss after training to evaluate the performance of the model.
    const double final_loss = model.compute_loss(gradient_predictions_multi, gradient_dataset_multi);

    std::cout << "Initial Loss: " << initial_loss << std::endl;
    std::cout << "Final Loss: " << final_loss << std::endl;
    // Check if the dataset is not empty and if the final loss is less than the initial loss, indicating that the model has improved during training.
    if (!gradient_dataset_multi.empty() && final_loss < initial_loss) {
        std::cout << "Test Passed: Multi-loss decreased." << std::endl;
    } else {
        std::cerr << "Test Failed: Multi-loss did not decrease." << std::endl;
    }
    std::cout << "Learned Omegas: " << model.omegas[0] << ", " << model.omegas[1] << std::endl;
    std::cout << "Learned Beta: " << model.beta << std::endl;
    // Check if the learned parameters (omegas and beta) are close to the true values used to generate the dataset, within a specified tolerance.
    if (std::abs(model.omegas[0] - trueOmega1) < testTolerance && std::abs(model.omegas[1] - trueOmega2) < testTolerance && std::abs(model.beta - trueBeta) < testTolerance) {
        std::cout << "Test Passed: Multi-parameters are close to true values." << std::endl;
    } else {
        std::cerr << "Test Failed: Multi-parameters are not close to true values." << std::endl;
    }
}

int main() {
    configureRunParametersFromConsole(); // Allows user to set parameters or use defaults
    // Generates dataset for single linear regression and multi-linear regression
    generateDataset(numPoints, trueOmega1, trueBeta, noiseLevel);
    generateMultiDataset(numPoints, trueOmega1, trueOmega2, trueBeta, noiseLevel);
    // Runs tests for normal regression, gradient regression, and multi-linear gradient regression
    test_normal_regression();
    test_gradient_regression();
    configureRunParametersFromConsoleMulti();
    test_multi_regression();
    return 0;
}

