#include "task-2.h"
#include <iostream>
#include <vector>
#include <random>
#include <fstream>

//Function to generate a CSV file with two X-coords and one Y-coord for multi-linear regression formula

void generateMultiDataset(int num_points, double trueOmega1, double trueOmega2, double trueBeta, double noise_level) {
    //Sets up random number gen and distributors to create data points
    std::mt19937 gen(42); 
    std::uniform_real_distribution<double> uniform(0.0, 1.0);
    std::normal_distribution<double> normal(0.0, noise_level);
    //initiallises vectors for storing data points
    std::vector<double> X1, X2, y;

    //creates number of data points specified by num_points
    for (int i = 0; i < num_points; ++i) {
        double x1_val = 2.0 * uniform(gen);
        X1.push_back(x1_val);

        double x2_val = 4.0 * uniform(gen);  //Second X-point gen
        X2.push_back(x2_val);

        //creates Y-val based of function parameters and noise
        double noise = 0.25 * normal(gen);
        double y_val = trueBeta + trueOmega2 * x2_val + trueOmega1 * x1_val + noise;
        y.push_back(y_val);


    }

    //Writes each data point to CSV file and adds header of x1,x2,y
    std::ofstream outFile("dataMulti.csv");
    outFile << "X1,X2,y\n"; // Header
    for (size_t i = 0; i < X1.size(); ++i) {
        outFile << X1[i] << ","<< X2[i] << "," << y[i] << "\n";
    }
    outFile.close();
}