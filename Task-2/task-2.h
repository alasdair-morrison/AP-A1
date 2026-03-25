#ifndef TASK_2_H
#define TASK_2_H

#include <vector>

struct DataPoint {
    double x;
    double y;
};

// Global variables
extern double omega; // slope
extern double beta;  // intercept
extern double eta;   // learning rate
extern int epochs;   // iterations

extern std::vector<DataPoint> dataset;
extern std::vector<DataPoint> predictions;

// Function declarations
std::vector<DataPoint> load_data();
std::vector<DataPoint> predict(const std::vector<DataPoint>& dataset);
double compute_loss(const std::vector<DataPoint>& predictions, const std::vector<DataPoint>& dataset);
void update_parameters();
std::vector<DataPoint> generateDataset(int num_points, double k, double m, double noise_level);

#endif // TASK_2_H
