#include "utils/decision_tree.hpp"
#include <vector>
#include <iostream>
using namespace std;

int main()
{
    // Training data: Height and Weight (scaled)
    vector<vector<double>> X = {
        {2.5, 1.5}, // Healthy
        {1.0, 3.5}, // Overweight
        {3.5, 0.5}, // Healthy
        {3.0, 2.0}, // Healthy
        {0.5, 4.0}, // Overweight
        {4.0, 1.0}, // Healthy
        {1.5, 3.0}, // Overweight
        {2.0, 2.5}  // Healthy
    };

    vector<double> y = {0, 1, 0, 0, 1, 0, 1, 0}; // 0 = Healthy, 1 = Overweight

    // Create decision tree with max depth 3
    DecisionTree dt(3);
    dt.fit(X, y);

    // Test samples
    vector<vector<double>> X_test = {
        {1.5, 2.0}, // Likely Overweight
        {3.0, 1.0}, // Likely Healthy
        {0.5, 4.0}, // Overweight
        {2.5, 2.0}  // Healthy
    };

    // Make predictions
    vector<int> predictions = dt.predict(X_test);

    // Print results
    for (size_t i = 0; i < X_test.size(); ++i)
    {
        cout << "Sample " << i + 1
             << " (Height=" << X_test[i][0]
             << ", Weight=" << X_test[i][1]
             << ") -> Prediction: "
             << (predictions[i] == 0 ? "Healthy" : "Overweight")
             << endl;
    }

    return 0;
}
