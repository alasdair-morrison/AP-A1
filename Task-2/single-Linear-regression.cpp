#include <iostream>
#include <vector>
#include <iomanip>
#include <stdexcept>

namespace sklearn_cpp {
namespace linear_model {

class LinearRegression {
private:
    double w;
    double b;
    double learning_rate;
    int epochs;

public:
    LinearRegression(double lr = 0.0001, int n_epochs = 1000)
        : w(0.0), b(0.0), learning_rate(lr), epochs(n_epochs) {}

    void fit(const std::vector<double>& X, const std::vector<double>& y) {
        if (X.empty() || y.empty()) {
            throw std::invalid_argument("X and y must not be empty.");
        }

        if (X.size() != y.size()) {
            throw std::invalid_argument("X and y must have the same size.");
        }

        const int m = static_cast<int>(X.size());

        for (int iter = 0; iter < epochs; ++iter) {
            double dw = 0.0;
            double db = 0.0;

            for (int i = 0; i < m; ++i) {
                double y_pred = w * X[i] + b;
                double error = y_pred - y[i];

                dw += error * X[i];
                db += error;
            }

            dw = (2.0 / m) * dw;
            db = (2.0 / m) * db;

            w -= learning_rate * dw;
            b -= learning_rate * db;
        }
    }

    std::vector<double> predict(const std::vector<double>& X) const {
        if (X.empty()) {
            throw std::invalid_argument("Input X must not be empty.");
        }

        std::vector<double> predictions;
        predictions.reserve(X.size());

        for (double x : X) {
            predictions.push_back(w * x + b);
        }

        return predictions;
    }

    double predict_single(double x) const {
        return w * x + b;
    }

    double mean_squared_error(const std::vector<double>& X,
                              const std::vector<double>& y) const {
        if (X.empty() || y.empty()) {
            throw std::invalid_argument("X and y must not be empty.");
        }

        if (X.size() != y.size()) {
            throw std::invalid_argument("X and y must have the same size.");
        }

        double mse = 0.0;
        int m = static_cast<int>(X.size());

        for (int i = 0; i < m; ++i) {
            double error = predict_single(X[i]) - y[i];
            mse += error * error;
        }

        return mse / m;
    }

    double get_weight() const { return w; }
    double get_bias() const { return b; }
};

} // namespace linear_model
} // namespace sklearn_cpp

int main() {
    using sklearn_cpp::linear_model::LinearRegression;

    try {
        // Example dataset: one input feature and one output
        // Replace these with your actual assignment data
        std::vector<double> X = {1, 2, 3, 4, 5, 6};
        std::vector<double> y = {3, 5, 7, 9, 11, 13};

        // Create model
        LinearRegression model(0.01, 5000);

        // Train model
        model.fit(X, y);

        // Print learned parameters
        std::cout << std::fixed << std::setprecision(4);
        std::cout << "Learned weight (w): " << model.get_weight() << "\n";
        std::cout << "Learned bias (b): " << model.get_bias() << "\n";

        // Predict on training data
        std::vector<double> predictions = model.predict(X);

        std::cout << "\nPredictions on training data:\n";
        std::cout << "X\tActual y\tPredicted y\n";
        for (size_t i = 0; i < X.size(); ++i) {
            std::cout << X[i] << "\t" << y[i] << "\t\t" << predictions[i] << "\n";
        }

        // Calculate error
        double mse = model.mean_squared_error(X, y);
        std::cout << "\nMean Squared Error: " << mse << "\n";

        // Predict new unseen values
        std::vector<double> X_new = {7, 8, 10};

        std::vector<double> new_predictions = model.predict(X_new);

        std::cout << "\nPredictions for new values:\n";
        for (size_t i = 0; i < X_new.size(); ++i) {
            std::cout << "x = " << X_new[i]
                      << " -> y = " << new_predictions[i] << "\n";
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
        return 1;
    }

    return 0;
}
