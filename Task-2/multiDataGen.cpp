#include "task-2.h"
#include <iostream>
#include <vector>
#include <random>
#include <fstream>

void generateDataset(int num_points, double trueOmega, double trueBeta, double noise_level) {
    std::mt19937 gen(42); 
    
    std::uniform_real_distribution<double> uniform(0.0, 1.0);
    
    std::normal_distribution<double> normal(0.0, noise_level);

    std::vector<double> X1, X2, y;

    for (int i = 0; i < num_points; ++i) {
        double x_val = 2.0 * uniform(gen);
        X1.push_back(x_val);

        double x_val = 2.0 * uniform(gen);  //Second X-point gen
        X2.push_back(x_val);


        double noise = 0.25 * normal(gen);
        double y_val = trueOmega + trueBeta * x_val + noise;
        y.push_back(y_val);


    }

    std::ofstream outFile("data.csv");
    outFile << "X,y\n"; // Header
    for (size_t i = 0; i < X1.size(); ++i) {
        outFile << X1[i] << ","<< X2[i] << "," << y[i] << "\n";
    }
    outFile.close();
}