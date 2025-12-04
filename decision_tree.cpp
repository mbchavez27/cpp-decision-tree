#include "utils/decision_tree.hpp"
#include <iostream>

DecisionTree::DecisionTree(int max_depth)
{
    this->max_depth = max_depth;
    this->root = nullptr;
}

void DecisionTree::fit(const vector<vector<double>> &X, const vector<double> &y)
{
    vector<int> labels(y.begin(), y.end());
    root = build_tree(X, labels, 0);
}

int DecisionTree::predict(const vector<double> &X)
{
    Node *node = root;

    while (!node->is_leaf)
    {
        if (X[node->feature_index] > node->threshold)
        {
            node = node->left;
        }
        else
        {
            node = node->right;
        }
    }

    return node->label;
}

vector<int> DecisionTree::predict(const vector<vector<double>> &X)
{
}

Node *build_tree(const vector<vector<double>> &X, const vector<int> &y, int depth)
{
}