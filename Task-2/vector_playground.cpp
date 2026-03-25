#include <iostream>
#include <vector>
#include <numeric> // Required for std::accumulate

int main() {
    // 1. Declaration
    // specific_type variable_name;
    std::vector<int> numbers;

    // 2. Adding elements (push_back adds to the end)
    numbers.push_back(10);
    numbers.push_back(20);
    numbers.push_back(30);

    // 3. Accessing elements
    std::cout << "First element: " << numbers[0] << std::endl;
    std::cout << "Second element: " << numbers.at(1) << std::endl; // .at() is safer check bounds

    // 4. Size
    std::cout << "Current size: " << numbers.size() << std::endl;

    // 5. Iteration (Looping through)
    std::cout << "All numbers: ";
    for (int i = 0; i < numbers.size(); ++i) {
        std::cout << numbers[i] << " ";
    }
    std::cout << std::endl;

    // 6. Removing elements (pop_back removes the last one)
    numbers.pop_back(); // Removes 30
    std::cout << "Size after pop_back: " << numbers.size() << std::endl;

    // --- Part 2: Vector of Vectors (2D Grid) ---
    std::cout << "\n--- Vector of Vectors ---" << std::endl;

    int rows = 5;
    int cols = 5;
    int defaultValue = 1;

    // Syntax: vector<vector<Type>> variableName(rows, vector<Type>(cols, defaultValue));
    std::vector<std::vector<int>> grid(rows, std::vector<int>(cols, defaultValue));

    // Accessing elements: grid[row][column]
    grid[0][0] = 1;
    grid[1][1] = 5;
    grid[2][3] = 9;

    // Printing the grid
    for (int i = 0; i < grid.size(); ++i) { // Loop through rows
        for (int j = 0; j < grid[i].size(); ++j) { // Loop through columns of current row
            grid[i][j] = (i+1) * (j+1); // Just filling with some values for demonstration
        }
    }

    // Printing the grid
    for (int i = 0; i < grid.size(); ++i) { // Loop through rows
        for (int j = 0; j < grid[i].size(); ++j) { // Loop through columns of current row
            std::cout << grid[i][j] << " ";
        }
        std::cout << std::endl;
    }
// --- Part 3: Summing Vector Elements ---
    std::cout << "\n--- Summing Vector Elements ---" << std::endl;
    
    std::vector<int> scores = {10, 20, 30, 40, 50};
    
    // Method 1: Using a loop
    int sum_loop = 0;
    for (int score : scores) {
        sum_loop += score;
    }
    std::cout << "Sum using loop: " << sum_loop << std::endl;

    // Method 2: Using std::accumulate (from <numeric>)
    // std::accumulate(start_iterator, end_iterator, initial_value)
    int sum_accumulate = std::accumulate(scores.begin(), scores.end(), 0);
    std::cout << "Sum using std::accumulate: " << sum_accumulate << std::endl;

    // --- Part 4: Summing a 2D Vector ---
    std::cout << "\n--- Summing a 2D Vector ---" << std::endl;
    
    long long total_grid_sum = 0;
    
    // Using range-based for loops for cleaner syntax
    for (const auto& row : grid) {      // Iterate through each row (which is a vector<int>)
        for (int val : row) {           // Iterate through each value in the row
            total_grid_sum += val;
        }
    }
    std::cout << "Total sum of grid elements: " << total_grid_sum << std::endl;

    return 0;
}
