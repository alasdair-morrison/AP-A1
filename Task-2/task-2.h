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
    double x1;
    double x2;
    double y;
};

extern std::vector<DataPoint> gradient_dataset;
extern std::vector<DataPoint> gradient_predictions;

extern std::vector<DataPoints> gradient_dataset_multi;
extern std::vector<DataPoints> gradient_predictions_multi;

#endif // TASK_2_H