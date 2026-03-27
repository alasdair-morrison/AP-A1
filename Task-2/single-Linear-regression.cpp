#include <iostream>
#include <vector>
#include <random>
#include <iomanip>
#include <fstream>
#include <stdexcept>

using namespace std;

/*
Assignment 01 - Task 2
Simple Linear Regression using Normal Equation in C++

This program generates a synthetic dataset based on the equation
y = kx + m with small random noise added to the output.

It then computes the parameters of the best-fit line:
y = wx + b

The parameters w and b are obtained using the analytical
normal equation formula.

Compilation:
g++ -std=c++11 main.cpp -o regression

Run:
./regression
*/

// Generate synthetic data using a straight line with noise
void generateData(vector<double>& X, vector<double>& y, int n, double true_w, double true_b) {
    random_device rd;
    mt19937 gen(rd());

    uniform_real_distribution<double> x_dist(0.0, 10.0);
    normal_distribution<double> noise_dist(0.0, 1.0);

    for (int i = 0; i < n; i++) {
        double x = x_dist(gen);
        double noise = noise_dist(gen);
        double target = true_w * x + true_b + noise;

        X.push_back(x);
        y.push_back(target);
    }
}

// Save generated data into a CSV file for optional plotting
void saveToCSV(const vector<double>& X, const vector<double>& y, const string& filename) {
    ofstream file(filename);

    if (!file.is_open()) {
        throw runtime_error("Unable to open file.");
    }

    file << "x,y\n";
    for (size_t i = 0; i < X.size(); i++) {
        file << X[i] << "," << y[i] << "\n";
    }

    file.close();
}

// Compute the mean of values in a vector
double mean(const vector<double>& values) {
    double sum = 0.0;
    for (double value : values) {
        sum += value;
    }
    return sum / values.size();
}

// Compute slope and intercept using the normal equation
void normalEquation(const vector<double>& X, const vector<double>& y, double& w, double& b) {
    if (X.empty() || y.empty() || X.size() != y.size()) {
        throw invalid_argument("X and y must be non-empty and of equal size.");
    }

    double x_mean = mean(X);
    double y_mean = mean(y);

    double numerator = 0.0;
    double denominator = 0.0;

    // Compute the numerator and denominator of the slope formula
    for (size_t i = 0; i < X.size(); i++) {
        numerator += (X[i] - x_mean) * (y[i] - y_mean);
        denominator += (X[i] - x_mean) * (X[i] - x_mean);
    }

    w = numerator / denominator;
    b = y_mean - w * x_mean;
}

int main() {
    try {
        vector<double> X;
        vector<double> y;

        // True line used to generate the synthetic dataset
        double true_w = 3.0;
        double true_b = 5.0;

        // Generate noisy dataset
        generateData(X, y, 100, true_w, true_b);

        // Save dataset to CSV file
        saveToCSV(X, y, "data.csv");

        double learned_w = 0.0;
        double learned_b = 0.0;

        // Compute the best-fit line using the normal equation
        normalEquation(X, y, learned_w, learned_b);

        cout << fixed << setprecision(6);
        cout << "===== Simple Linear Regression using Normal Equation =====\n\n";

        cout << "True parameters used to generate data:\n";
        cout << "w = " << true_w << ", b = " << true_b << "\n\n";

        cout << "Learned parameters:\n";
        cout << "w = " << learned_w << ", b = " << learned_b << "\n\n";

        cout << "Dataset has been saved to data.csv\n";
    }
    catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
        return 1;
    }

    return 0;
}