#include <iostream>
#include <vector>
#include <random>

// Completely chatgpted code. I will revise this on a later date.

int main() {
    // 1. Setup Randomness (equivalent to np.random.seed(42))
    std::mt19937 gen(42); 
    
    // Uniform distribution for X: [0.0, 1.0)
    std::uniform_real_distribution<double> uniform(0.0, 1.0);
    
    // Normal (Gaussian) distribution for noise: mean 0, std_dev 1
    std::normal_distribution<double> normal(0.0, 1.0);

    std::vector<double> X, y;
    int n = 100;

    for (int i = 0; i < n; ++i) {
        // X = 2 * np.random.rand(100, 1)
        double x_val = 2.0 * uniform(gen);
        X.push_back(x_val);

        // y = 4 + 3x + 0.25 * Gaussian noise
        double noise = 0.25 * normal(gen);
        double y_val = 4.0 + 3.0 * x_val + noise;
        y.push_back(y_val);
    }

    return 0;
}