#include "task-2.h"
#include <iostream>
#include <vector>
#include <random>
#include <fstream>

//Function to generate a CSV file with one X-coord and one Y-coord for simple-linear regression formula
void generateDataset(int num_points, double trueOmega, double trueBeta, double noise_level) {
    //Creates random number generator to create datapoints, using special seed "42" (;
    std::mt19937 gen(42); 
    std::uniform_real_distribution<double> uniform(0.0, 1.0);
    std::normal_distribution<double> normal(0.0, noise_level);
    //Initialise vectors to store datapoints
    std::vector<double> X, y;

    //Creates number of X and Y data points specified by num_points
    for (int i = 0; i < num_points; ++i) {
        //generates X_vals
        double x_val = 2.0 * uniform(gen);
        X.push_back(x_val);

        //Generates noise
        double noise = 0.25 * normal(gen);
        //Generates Y_vals
        double y_val = trueBeta + trueOmega * x_val + noise;
        y.push_back(y_val);
    }

    //Writes all datapoints to CSV file with suitable header
    std::ofstream outFile("data.csv");
    outFile << "X,y\n"; // Header
    for (size_t i = 0; i < X.size(); ++i) {
        outFile << X[i] << "," << y[i] << "\n";
    }
    outFile.close();
}