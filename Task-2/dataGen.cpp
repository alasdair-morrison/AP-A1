#include <iostream>
#include <vector>
#include <random>
#include <fstream>


int main() {
    std::mt19937 gen(42); 
    
    std::uniform_real_distribution<double> uniform(0.0, 1.0);
    
    std::normal_distribution<double> normal(0.0, 1.0);

    std::vector<double> X, y;
    int n = 100;

    for (int i = 0; i < n; ++i) {
        double x_val = 2.0 * uniform(gen);
        X.push_back(x_val);

        double noise = 0.25 * normal(gen);
        double y_val = 4.0 + 3.0 * x_val + noise;
        y.push_back(y_val);
    }

    std::ofstream outFile("data.csv");
    outFile << "X,y\n"; // Header
    for (size_t i = 0; i < X.size(); ++i) {
        outFile << X[i] << "," << y[i] << "\n";
    }
    outFile.close();

    return 0;
}