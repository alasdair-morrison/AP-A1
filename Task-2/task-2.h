#ifndef TASK_2_H
#define TASK_2_H

#include <vector>
#include <stdexcept>
#include <string>


struct DataPoint {
    double x;
    double y;
};
std::vector<DataPoint> loadDatasetSingle(const std::string& filename);

void computeNormalEquation(const std::vector<DataPoint>& dataset);

std::vector<DataPoint> predictNormalEquation(const std::vector<DataPoint>& dataset);

double compute_loss(const std::vector<DataPoint>& predictions, const std::vector<DataPoint>& dataset);

struct DataPoints {
    double x1;
    double x2;
    double y;
};

extern std::vector<DataPoint> normal_dataset;
extern std::vector<DataPoint> normal_predictions;
extern double omega; // Slope
extern double beta;  // Intercept

extern std::vector<DataPoint> gradient_dataset;
extern std::vector<DataPoint> gradient_predictions;



extern std::vector<DataPoints> gradient_dataset_multi;
extern std::vector<DataPoints> gradient_predictions_multi;
void generateDataset(int num_points, double trueOmega, double trueBeta, double noise_level);
void generateMultiDataset(int num_points, double trueOmega, double trueBeta, double noise_level);
std::vector<DataPoint> loadDatasetSingle(const std::string& filename);
std::vector<DataPoints> loadDatasetMulti(const std::string& filename);
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
    void update__multi_parameters();
};

#endif // TASK_2_H