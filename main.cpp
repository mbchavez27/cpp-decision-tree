#include "utils/decision_tree.hpp"
#include <vector>
#include <iostream>
using namespace std;

int main()
{
    vector<vector<double>> X = {
        {2.5, 1.5},
        {1.0, 3.5},
        {3.5, 0.5},
        {3.0, 2.0}};

    vector<double> y = {0, 1, 0, 0};

    DecisionTree dt(5);

    dt.fit(X, y);

    vector<vector<double>> X_test = {
        {1.5, 2.0},
        {3.0, 1.0}};

    vector<int> predictions = dt.predict(X_test);

    for (int p : predictions)
    {
        cout << p << endl;
    }

    return 0;
}