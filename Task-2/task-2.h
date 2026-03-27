#ifndef TASK_2_H
#define TASK_2_H

#include <iostream>
#include <vector>
#include <iomanip>
#include <stdexcept>

struct DataPoint {
    double x;
    double y;
};

struct DataPoints {
    double x;
    double y1;
    double y2;
};

// Global variables
extern double omega; // slope
extern double beta;  // intercept
extern double eta;   // learning rate
extern int epochs;   // iterations
extern std::vector<double> omegas; // Slopes for multi-regression

extern std::vector<DataPoint> dataset;
extern std::vector<DataPoint> predictions;

extern std::vector<DataPoints> dataset_multi;
extern std::vector<DataPoints> predictions_multi;

// Function declarations
std::vector<DataPoint> load_data();
std::vector<DataPoint> predict(const std::vector<DataPoint>& dataset);
double compute_loss(const std::vector<DataPoint>& predictions, const std::vector<DataPoint>& dataset);
void update_parameters();
std::vector<DataPoint> generateDataset(int num_points, double k, double m, double noise_level);
std::vector<DataPoints> predict(const std::vector<DataPoints>& dataset);
double compute_loss(const std::vector<DataPoints>& predictions, const std::vector<DataPoints>& dataset);
void update__multi_parameters();
std::vector<DataPoints> generateMultiDataset(int num_points, double k1, double m1, double k2, double m2, double noise_level);
#endif // TASK_2_H