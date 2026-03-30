#include <iostream>
#include <cmath>
#include <iomanip>
#include <functional>

using namespace std;

// FUNCTION DEFINITIONS

// Example nonlinear equation: f(x) = x^3 - x - 2 = 0
// This function has a root near x = 1.5214
double f(double x) {
    return x * x * x - x - 2.0;
}

// Derivative of f(x): f'(x) = 3x^2 - 1
double f_derivative(double x) {
    return 3.0 * x * x - 1.0;
}

// Fixed-point iteration function: g(x) = x - f(x)/k
// We rearrange f(x) = 0 to x = g(x)
// For f(x) = x^3 - x - 2, one way is: x = (x^3 - 2)
// But a better convergent form is: x = (x + 2)^(1/3)
double g(double x) {
    return pow(x + 2.0, 1.0/3.0);
}

// FIXED-POINT ITERATION METHOD


double fixed_point_iteration(function<double(double)> g_func, 
                             double x0, 
                             double tolerance = 1e-6, 
                             int max_iterations = 100) {
    
    cout << "FIXED-POINT ITERATION METHOD" << endl;
    cout << "Initial guess x0 = " << x0 << endl;
    cout << "Tolerance = " << tolerance << endl;
    cout << "Max iterations = " << max_iterations << endl;
    cout << "\nIteration\tx_n\t\t|x_{n+1} - x_n|" << endl;
    
    double x_current = x0;  // Current approximation
    double x_next;          // Next approximation
    int iteration = 0;      // Iteration counter
    double error;           // Error between successive approximations
    
    // Main iteration loop
    do {
        iteration++;
        
        // Compute next approximation using fixed-point formula
        x_next = g_func(x_current);
        
        // Calculate absolute error between successive approximations
        error = abs(x_next - x_current);
        
        // Display iteration information
        cout << fixed << setprecision(8);
        cout << iteration << "\t\t" << x_current << "\t" << error << endl;
        
        // Update current approximation for next iteration
        x_current = x_next;
        
        // Check if maximum iterations reached
        if (iteration >= max_iterations) {
            cout << "\nWarning: Maximum iterations reached!" << endl;
            break;
        }
        
    } while (error > tolerance);  // Continue until error is below tolerance
    
    // Display final results
    cout << "\n--- Results ---" << endl;
    cout << "Converged after " << iteration << " iterations" << endl;
    cout << "Approximate root: x = " << fixed << setprecision(10) << x_current << endl;
    cout << "f(x) = " << f(x_current) << endl;
    
    return x_current;
}

// NEWTON-RAPHSON METHOD


double newton_raphson(function<double(double)> f_func,
                     function<double(double)> f_prime,
                     double x0,
                     double tolerance = 1e-6,
                     int max_iterations = 100) {
    
    cout << "NEWTON-RAPHSON METHOD" << endl;
    cout << "Initial guess x0 = " << x0 << endl;
    cout << "Tolerance = " << tolerance << endl;
    cout << "Max iterations = " << max_iterations << endl;
    cout << "\nIteration\tx_n\t\tf(x_n)\t\t|x_{n+1} - x_n|" << endl;
    
    double x_current = x0;  // Current approximation
    double x_next;          // Next approximation
    int iteration = 0;      // Iteration counter
    double error;           // Error between successive approximations
    double f_value;         // Value of f at current point
    double f_prime_value;   // Value of f' at current point
    
    // Main iteration loop
    do {
        iteration++;
        
        // Evaluate function and its derivative at current point
        f_value = f_func(x_current);
        f_prime_value = f_prime(x_current);
        
        // Check if derivative is too close to zero (potential division by zero)
        if (abs(f_prime_value) < 1e-12) {
            cout << "\nError: Derivative too close to zero!" << endl;
            cout << "Newton-Raphson method fails at this point." << endl;
            return x_current;
        }
        
        // Apply Newton-Raphson formula
        x_next = x_current - f_value / f_prime_value;
        
        // Calculate absolute error
        error = abs(x_next - x_current);
        
        // Display iteration information
        cout << fixed << setprecision(8);
        cout << iteration << "\t\t" << x_current << "\t" << f_value << "\t" << error << endl;
        
        // Update current approximation for next iteration
        x_current = x_next;
        
        // Check if maximum iterations reached
        if (iteration >= max_iterations) {
            cout << "\nWarning: Maximum iterations reached!" << endl;
            break;
        }
        
    } while (error > tolerance);  // Continue until error is below tolerance
    
    // Display final results
    cout << "\n--- Results ---" << endl;
    cout << "Converged after " << iteration << " iterations" << endl;
    cout << "Approximate root: x = " << fixed << setprecision(10) << x_current << endl;
    cout << "f(x) = " << f(x_current) << endl;
    
    return x_current;
}


// MAIN FUNCTION


int main() {
    cout << "NONLINEAR EQUATION SOLVER" << endl;
    cout << "\nSolving: f(x) = x^3 - x - 2 = 0" << endl;
    cout << "Known root is approximately x ≈ 1.5214" << endl;
    
    // Parameters
    double initial_guess = 1.0;    // Starting point for iterations
    double tolerance = 1e-6;       // Convergence criterion
    int max_iter = 100;            // Maximum iterations allowed
    
    
    double root_fixed_point = fixed_point_iteration(g, initial_guess, tolerance, max_iter);

    
    double root_newton = newton_raphson(f, f_derivative, initial_guess, tolerance, max_iter);
    
    
    cout << "COMPARISON OF METHODS" << endl;

    cout << fixed << setprecision(10);
    cout << "Fixed-Point root:     " << root_fixed_point << endl;
    cout << "Newton-Raphson root:  " << root_newton << endl;
    cout << "\nNote: Newton-Raphson typically converges faster" << endl;
    cout << "but requires derivative computation." << endl;
    
    
    cout << "\n========================================" << endl;
    cout << "Try with your own initial guess? (y/n): ";
    char choice;
    cin >> choice;
    
    if (choice == 'y' || choice == 'Y') {
        double user_guess;
        cout << "Enter initial guess: ";
        cin >> user_guess;
        
        cout << "\nChoose method:" << endl;
        cout << "1. Fixed-Point Iteration" << endl;
        cout << "2. Newton-Raphson" << endl;
        cout << "Enter choice (1 or 2): ";
        int method_choice;
        cin >> method_choice;
        
        if (method_choice == 1) {
            fixed_point_iteration(g, user_guess, tolerance, max_iter);
        } else if (method_choice == 2) {
            newton_raphson(f, f_derivative, user_guess, tolerance, max_iter);
        } else {
            cout << "Invalid choice!" << endl;
        }
    }
    
    return 0;
}
