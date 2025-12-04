#include "utils/decision_tree.hpp"
#include "utils/gini.hpp"
#include <algorithm>
#include <iostream>
#include <set>

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

Node *build_tree(const vector<vector<double>> &X, const vector<int> &y, int depth, int max_depth)
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
    double best_gini = 0.0;

    for (int features = 0; X[0].size(); ++features)
    {
        set<double> thresholds;
        for (int i = 0; i < X.size(); ++i)
        {
            thresholds.insert(X[i][features]);
        }

        for (double threshold : thresholds)
        {
            vector<int> left_y, right_y;
            for (int i = 0; i < X.size(); i++)
            {
                if (X[i][features] <= threshold)
                    left_y.push_back(X[i][features]);
                else
                    right_y.push_back(X[i][features]);
            }

            if (left_y.empty() || right_y.empty())
                continue;

            Node left_node, right_node;
            left_node.labels = left_y;
            right_node.labels = right_y;

            double gini = gini_split(left_y, right_y);

            if (gini < best_gini)
            {
                best_gini = gini;
                best_feature = features;
                best_threshold = threshold;
            }
        }
    }
}