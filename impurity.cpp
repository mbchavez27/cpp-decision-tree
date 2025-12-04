#include <iostream>
#include "utils/impurity.hpp"
using namespace std;

double gini_impurity(const vector<int> &y)
{
    double total_fraction_squared = 0;
    double sum_counts = y.size();
    for (int i = 0; i < y.size(); i++)
    {
        double fraction = static_cast<double>(y[i]) / sum_counts;
        total_fraction_squared += fraction * fraction;
    }

    double impurity = 1.0 - total_fraction_squared;

    double impurity;
}
