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

double gini_split(Node *node)
{
    if (!node->left || !node->right)
        return 0.0;

    double left_label = static_cast<double>(node->left->labels.size());
    double right_label = static_cast<double>(node->right->labels.size());
    double label_totals = left_label + right_label;

    double gini_left = gini_impurity(node->left->labels);
    double gini_right = gini_impurity(node->right->labels);

    return ((left_label / label_totals) * gini_left) + ((right_label / label_totals) * gini_right);
}
