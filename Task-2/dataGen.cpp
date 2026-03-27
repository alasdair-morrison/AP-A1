#include "task-2.h"
#include <iostream>
#include <vector>
#include <random>
#include <fstream>

void generateDataset(int num_points, double trueOmega, double trueBeta, double noise_level) {
    std::mt19937 gen(42); 
    
    std::uniform_real_distribution<double> uniform(0.0, 1.0);
    
    std::normal_distribution<double> normal(0.0, noise_level);

    std::vector<double> X, y;

    for (int i = 0; i < num_points; ++i) {
        double x_val = 2.0 * uniform(gen);
        X.push_back(x_val);

        double noise = 0.25 * normal(gen);
        double y_val = trueBeta + trueOmega * x_val + noise;
        y.push_back(y_val);
    }

    std::ofstream outFile("data.csv");
    outFile << "X,y\n"; // Header
    for (size_t i = 0; i < X.size(); ++i) {
        outFile << X[i] << "," << y[i] << "\n";
    }
    outFile.close();
}