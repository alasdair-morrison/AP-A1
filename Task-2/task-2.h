#ifndef TASK_2_H
#define TASK_2_H

#include <vector>
#include <stdexcept>

struct DataPoint {
    double x;
    double y;
};

struct DataPoints {
    double x1;
    double x2;
    double y;
};

extern std::vector<DataPoint> gradient_dataset;
extern std::vector<DataPoint> gradient_predictions;

namespace sklearn_cpp {
namespace linear_model {

class LinearRegression {
private:
    double w;
    double b;
    double learning_rate;
    int epochs;

public:
    LinearRegression(double lr = 0.0001, int n_epochs = 1000);

    void fit(const std::vector<double>& X, const std::vector<double>& y);

    std::vector<double> predict(const std::vector<double>& X) const;

    double predict_single(double x) const;

    double mean_squared_error(const std::vector<double>& X,
                              const std::vector<double>& y) const;

    double get_weight() const;
    double get_bias() const;
};

} // namespace linear_model
} // namespace sklearn_cpp

extern std::vector<DataPoints> gradient_dataset_multi;
extern std::vector<DataPoints> gradient_predictions_multi;

class GradientRegression {
private:
    double omega; // Slope
    double beta;  // Intercept
    double eta;   // Learning rate
    int epochs;   // Number of iterations

public:
    GradientRegression(double learning_rate, int num_epochs);
    std::vector<DataPoint> predict(const std::vector<DataPoint>& dataset);
    double compute_loss(const std::vector<DataPoint>& predictions, const std::vector<DataPoint>& dataset);
    double compute_omega_gradient(const std::vector<DataPoint>& predictions, const std::vector<DataPoint>& dataset);
    double compute_beta_gradient(const std::vector<DataPoint>& predictions, const std::vector<DataPoint>& dataset);
    void update_parameters();
};

class MultiGradientRegression {
private:
    std::vector<double> omegas; // Slopes for each feature
    double beta;                // Intercept
    double eta;                 // Learning rate
    int epochs;                 // Number of iterations

public:
    MultiGradientRegression(int num_features, double learning_rate, int num_epochs);
    std::vector<DataPoints> predict(const std::vector<DataPoints>& dataset);
    double compute_loss(const std::vector<DataPoints>& predictions, const std::vector<DataPoints>& dataset);
    void update__multi_parameters();
};

#endif // TASK_2_H