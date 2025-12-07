#include "../utils/decision_tree.hpp"
#include "../utils/gini.hpp"
#include <algorithm>
#include <iostream>
#include <set>
#include <limits>

DecisionTree::DecisionTree(int max_depth)
{
    this->max_depth = max_depth;
    this->root = nullptr;
}

void DecisionTree::fit(const vector<vector<double>> &X, const vector<double> &y)
{
    vector<int> labels(y.begin(), y.end());
    root = build_tree(X, labels, 0, max_depth);
}

int DecisionTree::predict(const vector<double> &X)
{
    Node *node = root;

    while (!node->is_leaf)
    {
        if (X[node->feature_index] <= node->threshold)
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
    vector<int> predictions;
    for (const auto &sample : X)
    {
        predictions.push_back(predict(sample));
    }

    return predictions;
}

Node *DecisionTree::build_tree(const vector<vector<double>> &X, const vector<int> &y, int depth, int max_depth)
{
    Node *node = new Node();
    node->depth = depth;

    // Stopping Condition
    bool all_same = all_of(y.begin(), y.end(), [&](int val)
                           { return val == y[0]; }); // Stopping Criterion: Check if a node is pure and should become a leaf. Meaning no split can improve it

    if (all_same || depth >= max_depth)
    {
        node->is_leaf = true;
        node->label = y[0];
        node->labels = y;
        return node;
    }

    int best_feature = -1;
    double best_threshold = 0.0;
    double best_gini = numeric_limits<double>::max();

    for (size_t features = 0; features < X[0].size(); ++features)
    {
        // Adds all threshold
        set<double> thresholds;
        for (size_t i = 0; i < X.size(); ++i)
        {
            thresholds.insert(X[i][features]);
        }

        // Loops through the thresholds to check if given features is less then or greater than treshhold to split data
        for (double threshold : thresholds)
        {
            vector<int> left_y, right_y;

            // Split Data
            for (size_t i = 0; i < X.size(); i++)
            {
                if (X[i][features] <= threshold)
                    left_y.push_back(y[i]);
                else
                    right_y.push_back(y[i]);
            }

            if (left_y.empty() || right_y.empty())
                continue;

            // Calculate Gini Impurity
            double gini = gini_split(left_y, right_y);

            // Update Best Gini
            if (gini < best_gini)
            {
                best_gini = gini;
                best_feature = features;
                best_threshold = threshold;
            }
        }
    }

    // Fallback If no Best Feature
    if (best_feature == -1)
    {
        node->is_leaf = true;
        node->label = y[0];
        node->labels = y;
        return node;
    }

    // Split Data
    vector<vector<double>> left_X, right_X;
    vector<int> left_y, right_y;
    for (size_t i = 0; i < X.size(); i++)
    {
        if (X[i][best_feature] <= best_threshold)
        {
            left_X.push_back(X[i]);
            left_y.push_back(y[i]);
        }
        else
        {
            right_X.push_back(X[i]);
            right_y.push_back(y[i]);
        }
    }

    node->feature_index = best_feature;
    node->threshold = best_threshold;
    node->left = build_tree(left_X, left_y, depth + 1, max_depth);
    node->right = build_tree(right_X, right_y, depth + 1, max_depth);

    return node;
}