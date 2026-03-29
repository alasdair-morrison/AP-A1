#ifndef TASK_2_H
#define TASK_2_H

#include <vector>
#include <stdexcept>
#include <string>
// Structure to represent a single data point for single linear regression
struct DataPoint {
    double x;
    double y;
};
// Function declarations for dataset generation, loading, and regression methods for normal equation method
std::vector<DataPoint> loadDatasetSingle(const std::string& filename);
void computeNormalEquation(const std::vector<DataPoint>& dataset);
std::vector<DataPoint> predictNormalEquation(const std::vector<DataPoint>& dataset);
double compute_loss(const std::vector<DataPoint>& predictions, const std::vector<DataPoint>& dataset);
// Global variables for normal regression calculations
extern std::vector<DataPoint> normal_dataset;
extern std::vector<DataPoint> normal_predictions;
extern double omega; // Slope
extern double beta;  // Intercept
// Structure to represent a single data point for multi-linear regression
struct DataPoints {
    double x1;
    double x2;
    double y;
};
// Global variables for gradient regression calculations
extern std::vector<DataPoint> gradient_dataset;
extern std::vector<DataPoint> gradient_predictions;
extern std::vector<DataPoints> gradient_dataset_multi;
extern std::vector<DataPoints> gradient_predictions_multi;
// Function delclarations for dataset generation and loading
void generateDataset(int num_points, double trueOmega, double trueBeta, double noise_level);
void generateMultiDataset(int num_points, double trueOmega1, double trueOmega2, double trueBeta, double noise_level);
std::vector<DataPoint> loadDatasetSingle(const std::string& filename);
std::vector<DataPoints> loadDatasetMulti(const std::string& filename);
// Class declarations for single linear regression using gradient descent method and multi-linear regression using gradient descent method
class GradientRegression {
private:
    double eta;   // Learning rate
    int epochs;   // Number of iterations
    std::string datasetFilename;

public:
    double omega; // Slope
    double beta;  // Intercept
    GradientRegression(double learning_rate, int num_epochs, std::string datasetFilename);
    void predict(const std::vector<DataPoint>& dataset);
    double compute_loss(const std::vector<DataPoint>& predictions, const std::vector<DataPoint>& dataset);
    double compute_omega_gradient(const std::vector<DataPoint>& predictions, const std::vector<DataPoint>& dataset);
    double compute_beta_gradient(const std::vector<DataPoint>& predictions, const std::vector<DataPoint>& dataset);
    void update_parameters();
};

class MultiGradientRegression {
private:
    double eta;                 // Learning rate
    int epochs;                 // Number of iterations
    std::string datasetFilename;

public:
    std::vector<double> omegas; // Slopes for each feature
    double beta;                // Intercept
    MultiGradientRegression(double learning_rate, int num_epochs, std::string datasetFilename);
    void predict(const std::vector<DataPoints>& dataset);
    double compute_loss(const std::vector<DataPoints>& predictions, const std::vector<DataPoints>& dataset);
    void update_multi_parameters();
};

#endif // TASK_2_H