#include <iostream>
#include "utils/gini.hpp"
#include "utils/node.hpp"

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

    return 1.0 - total_fraction_squared;
}

double gini_split(const vector<int> &left_y, const vector<int> &right_y)
{
    double n_left = left_y.size();
    double n_right = right_y.size();
    double n_total = n_left + n_right;

    double gini_left = gini_impurity(left_y);
    double gini_right = gini_impurity(right_y);

    return (n_left / n_total) * gini_left + (n_right / n_total) * gini_right;
}
