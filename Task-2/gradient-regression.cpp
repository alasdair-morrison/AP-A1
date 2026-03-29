#include "task-2.h"
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
// Global variables for single linear regression
std::vector<DataPoint> gradient_dataset;
std::vector<DataPoint> gradient_predictions;
// Global variables for multi-linear regression
std::vector<DataPoints> gradient_dataset_multi;
std::vector<DataPoints> gradient_predictions_multi;
// Function to read the dataset from a CSV file and load it into a vector of DataPoint structures
std::vector<DataPoint>loadDatasetSingle(const std::string& filename) {
    std::vector<DataPoint> dataset;
    std::ifstream inFile(filename); // Open the specified file for reading
    if (!inFile) { // Check if the file was successfully opened
        throw std::runtime_error("Could not open file: " + filename); // If the file cannot be opened, throw an error
    }
    std::string line; 
    std::getline(inFile, line); // Skip header
    while (std::getline(inFile, line)) { // Read each line of the file until the end
        std::istringstream iss(line); // Create a string stream to parse the line
        std::string x_str, y_str; // Variables to hold the string representations of x and y values
        // Parse the line to extract x and y values, assuming they are separated by a comma
        if (std::getline(iss, x_str, ',') && std::getline(iss, y_str)) { 
            double x = std::stod(x_str); // Convert the x value from string to double
            double y = std::stod(y_str); // Convert the y value from string to double
            dataset.push_back({x, y});// Add the parsed data point to the dataset vector
        }
    }
    inFile.close(); // Close the file after reading is complete
    return dataset;
}
// Function to read the dataset for multi-linear regression from a CSV file and load it into a vector of DataPoints structures
std::vector<DataPoints> loadDatasetMulti(const std::string& filename) {
    std::vector<DataPoints> dataset;
    std::ifstream inFile(filename); // Open the specified file for reading
    if (!inFile) { // Check if the file was successfully opened
        throw std::runtime_error("Could not open file: " + filename); // If the file cannot be opened, throw an error
    }
    std::string line;
    std::getline(inFile, line); // Skip header
    while (std::getline(inFile, line)) { // Read each line of the file until the end
        std::istringstream iss(line); // Create a string stream to parse the line
        std::string x1_str, x2_str, y_str;
        // Parse the line to extract x1, x2, and y values, assuming they are separated by commas
        if (std::getline(iss, x1_str, ',') && std::getline(iss, x2_str, ',') && std::getline(iss, y_str)) {
            double x1 = std::stod(x1_str); // Convert the x1 value from string to double
            double x2 = std::stod(x2_str); // Convert the x2 value from string to double
            double y = std::stod(y_str); // Convert the y value from string to double
            dataset.push_back({x1, x2, y}); // Add the parsed data point to the dataset vector
        }
    }
    inFile.close(); // Close the file after reading is complete
    return dataset;
}
// Class instantiation for single linear regression using gradient descent method
// The constructor initializes the learning rate, number of epochs, and loads the dataset from the specified file.
GradientRegression::GradientRegression(double learning_rate, int num_epochs, std::string datasetFilename)
    : eta(learning_rate), epochs(num_epochs), datasetFilename(datasetFilename), omega(0.0), beta(0.0) {
    gradient_dataset = loadDatasetSingle(datasetFilename);
}
// Function to generate predictions based on the current parameters (omega and beta) for single linear gradient regression. 
// It iterates through the dataset and calculates the predicted y value for each x 
// using the formula y_pred = beta + omega * x, and stores the predictions in a vector.
void GradientRegression::predict(const std::vector<DataPoint>& dataset) {
    for (const auto& point : dataset) { // Iterate through each data point in the dataset
        double y_pred = beta + omega * point.x; // Calculate the predicted y value using current parameters
        gradient_predictions.push_back({point.x, y_pred}); // Store the predicted data point in the predictions vector
    }
}
// Function to compute the loss (e.g., mean squared error) for single linear regression by comparing the predicted values to the actual dataset values.
double GradientRegression::compute_loss(const std::vector<DataPoint>& predictions, const std::vector<DataPoint>& dataset) {
    double total_loss = 0.0;
    for (size_t i = 0; i < dataset.size(); ++i) { // Iterate through each data point in the dataset
        double diff = predictions[i].y - dataset[i].y; // Calculate the difference between the predicted y value and the actual y value
        total_loss += diff * diff; // Accumulate the squared differences to compute the total loss
    }
    return total_loss / (dataset.size() * 2); // Return the average loss (mean squared error)
}
// Function to compute the gradient of the loss with respect to omega (slope) for single linear regression.
double GradientRegression::compute_omega_gradient(const std::vector<DataPoint>& predictions, const std::vector<DataPoint>& dataset) {
    double gradient = 0.0;
    for (size_t i = 0; i < dataset.size(); ++i) { // Iterate through each data point in the dataset
        gradient += (predictions[i].y - dataset[i].y) * dataset[i].x; // Calculate the contribution to the gradient from each data point based on the difference between predicted and actual values, multiplied by the x value
    }
    return gradient / dataset.size(); // Return the average gradient over the dataset
}
// Function to compute the gradient of the loss with respect to beta (intercept) for single linear regression.
double GradientRegression::compute_beta_gradient(const std::vector<DataPoint>& predictions, const std::vector<DataPoint>& dataset) {
    double gradient = 0.0;
    for (size_t i = 0; i < dataset.size(); ++i) { // Iterate through each data point in the dataset
        gradient += predictions[i].y - dataset[i].y; // Calculate the contribution to the gradient from each data point based on the difference between predicted and actual values
    }
    return gradient / dataset.size(); // Return the average gradient over the dataset
}
// Function to update the parameters (omega and beta) for single linear regression using the computed gradients and the learning rate.
void GradientRegression::update_parameters() {
    // Compute the gradients for omega and beta
    double omega_gradient = compute_omega_gradient(gradient_predictions, gradient_dataset);
    double beta_gradient = compute_beta_gradient(gradient_predictions, gradient_dataset);
    // Update the parameters using the computed gradients and the learning rate
    omega -= eta * omega_gradient;
    beta -= eta * beta_gradient;
}
// Class instantiation for multi-linear regression using gradient descent method
// The constructor initializes the learning rate, number of epochs, and loads the dataset from the specified file.
MultiGradientRegression::MultiGradientRegression(double learning_rate, int num_epochs, std::string datasetFilename)
    : eta(learning_rate), epochs(num_epochs), datasetFilename(datasetFilename), omegas(2, 0.0), beta(0.0) {
    gradient_dataset_multi = loadDatasetMulti(datasetFilename);
}
// Function to generate predictions based on the current parameters (omegas and beta) for multi-linear gradient regression.
void MultiGradientRegression::predict(const std::vector<DataPoints>& dataset) {
    for (const auto& point : dataset) {
        // Calculate the predicted y value using the formula y_pred = beta + omega1 * x1 + omega2 * x2, where omegas[0] is the slope for x1 and omegas[1] is the slope for x2.
        double y_pred = beta + omegas[0] * point.x1 + omegas[1] * point.x2;
        gradient_predictions_multi.push_back({point.x1, point.x2, y_pred}); // Store the predicted data point in the predictions vector
    }
}
// Function to compute the loss (e.g., mean squared error) for multi-linear regression by comparing the predicted values to the actual dataset values.
double MultiGradientRegression::compute_loss(const std::vector<DataPoints>& predictions, const std::vector<DataPoints>& dataset) {
    double total_loss = 0.0;
    for (size_t i = 0; i < dataset.size(); ++i) {
        // Calculate the difference between the predicted y value and the actual y value for each data point, and accumulate the squared differences to compute the total loss.
        double diff = predictions[i].y - dataset[i].y;
        total_loss += diff * diff;
    }
    return total_loss / (2.0 * dataset.size()); // Return the average loss (mean squared error)
}
// Function to update the parameters (omegas and beta) for multi-linear regression using the computed gradients and the learning rate.
void MultiGradientRegression::update_multi_parameters() {
    double omega_gradient_x1 = 0.0;
    double omega_gradient_x2 = 0.0;
    double beta_gradient = 0.0;
    // Compute the gradients for omega1, omega2, and beta by iterating through the dataset and calculating the contribution from each 
    // data point based on the difference between predicted and actual values, multiplied by the respective x values for omega gradients.
    for (size_t i = 0; i < gradient_dataset_multi.size(); ++i) {
        const double diff = gradient_predictions_multi[i].y - gradient_dataset_multi[i].y;
        omega_gradient_x1 += diff * gradient_dataset_multi[i].x1;
        omega_gradient_x2 += diff * gradient_dataset_multi[i].x2;
        beta_gradient += diff;
    }

    // Average the gradients over the dataset
    omega_gradient_x1 /= gradient_dataset_multi.size();
    omega_gradient_x2 /= gradient_dataset_multi.size();
    beta_gradient /= gradient_dataset_multi.size();

    // Update parameters using the computed gradients
    omegas[0] -= eta * omega_gradient_x1; // Update for x1
    omegas[1] -= eta * omega_gradient_x2; // Update for x2
    beta -= eta * beta_gradient;           // Update for bias
}