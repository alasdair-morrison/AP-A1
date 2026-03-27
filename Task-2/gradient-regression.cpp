#include "task-2.h"
#include <vector>
#include <iostream>

std::vector<DataPoint> gradient_dataset;
std::vector<DataPoint> gradient_predictions;

std::vector<DataPoints> gradient_dataset_multi;
std::vector<DataPoints> gradient_predictions_multi;
class GradientRegression {
    private:
        double omega; // Slope
        double beta;  // Intercept
        double eta;   // Learning rate
        int epochs;   // Number of iterations
    public:
        GradientRegression(double learning_rate, int num_epochs)
            : omega(0.0), beta(0.0), eta(learning_rate), epochs(num_epochs) {}

        std::vector<DataPoint> predict(const std::vector<DataPoint>& dataset) {
            std::vector<DataPoint> predictions;
            for (const auto& point : dataset) {
                double y_pred = beta + omega * point.x;
                gradient_predictions.push_back({point.x, y_pred});   
            }
            return predictions;
        }
        double compute_loss(const std::vector<DataPoint>& predictions, const std::vector<DataPoint>& dataset) {
            double total_loss = 0.0;
            for (long i = 0; i < dataset.size(); ++i) {
                double diff = predictions[i].y - dataset[i].y;
                total_loss += diff * diff;
            }
            return total_loss/(dataset.size() * 2);
        }
        double compute_omega_gradient(const std::vector<DataPoint>& predictions, const std::vector<DataPoint>& dataset) {
            double gradient = 0.0;
            for (long i = 0; i < dataset.size(); ++i) {
                gradient += (predictions[i].y - dataset[i].y) * dataset[i].x;
            }
            return gradient / dataset.size();
        }

        double compute_beta_gradient(const std::vector<DataPoint>& predictions, const std::vector<DataPoint>& dataset) {
            double gradient = 0.0;
            for (long i = 0; i < dataset.size(); ++i) {
                gradient += predictions[i].y - dataset[i].y;
            }
            return gradient / dataset.size();
        }

        void update_parameters() {
            double omega_gradient = compute_omega_gradient(gradient_predictions, gradient_dataset);
            double beta_gradient = compute_beta_gradient(gradient_predictions, gradient_dataset);
            
            omega -= eta * omega_gradient;
            beta -= eta * beta_gradient;
        }
};

class MultiGradientRegression {
    private:
        std::vector<double> omegas; // Slopes for each feature
        double beta;  // Intercept
        double eta;   // Learning rate
        int epochs;   // Number of iterations
    public:
        MultiGradientRegression(int num_features, double learning_rate, int num_epochs)
            : omegas(num_features, 0.0), beta(0.0), eta(learning_rate), epochs(num_epochs) {}

        std::vector<DataPoints> predict(const std::vector<DataPoints>& dataset) {
            std::vector<DataPoints> predictions;
            for (const auto& point : dataset) {
                double x1_pred = beta + omegas[0] * point.x1; // Prediction for x1
                double x2_pred = beta + omegas[1] * point.x2; // Prediction for x2 (same as x1 in this simple model)
                predictions.push_back({point.y, x1_pred, x2_pred});
            }
            return predictions;
        }
        double compute_loss(const std::vector<DataPoints>& predictions, const std::vector<DataPoints>& dataset) {
            double total_loss = 0.0;
            for (long i = 0; i < dataset.size(); ++i) {
                double diff_y1 = predictions[i].x1 - dataset[i].x1;
                double diff_y2 = predictions[i].x2 - dataset[i].x2;
                total_loss += (diff_y1 * diff_y1 + diff_y2 * diff_y2) / 2.0; // Average loss for both predictions
            }
            return total_loss / dataset.size();
        }
        void update__multi_parameters() {
            double omega_gradient_x1 = 0.0;
            double omega_gradient_x2 = 0.0;
            double beta_gradient = 0.0;

            for (long i = 0; i < gradient_dataset_multi.size(); ++i) {
                double diff_x1 = gradient_predictions_multi[i].x1 - gradient_dataset_multi[i].x1;
                double diff_x2 = gradient_predictions_multi[i].x2 - gradient_dataset_multi[i].x2;

                omega_gradient_x1 += diff_x1 * gradient_dataset_multi[i].x1;
                omega_gradient_x2 += diff_x2 * gradient_dataset_multi[i].x2;
                beta_gradient += diff_x1 + diff_x2; // Sum of gradients for both predictions
            }

            // Average the gradients over the dataset
            omega_gradient_x1 /= gradient_dataset_multi.size();
            omega_gradient_x2 /= gradient_dataset_multi.size();
            beta_gradient /= (gradient_dataset_multi.size() * 2); // Average over both predictions

            // Update parameters using the computed gradients
            omegas[0] -= eta * omega_gradient_x1; // Update for x1
            omegas[1] -= eta * omega_gradient_x2; // Update for x2
            beta -= eta * beta_gradient;           // Update for bias
        }
};