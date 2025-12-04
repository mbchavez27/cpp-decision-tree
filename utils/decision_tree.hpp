#pragma once
#include "node.hpp"
#include <vector>
using namespace std;

class DecisionTree
{
public:
    DecisionTree(int max_depth = 5);
    void fit(const vector<vector<double>> &X, const vector<double> &y);
    int predict(const vector<double> &X);
    vector<int> predict(const vector<vector<double>> &X);

private:
    Node *root;
    int max_depth;
    Node *build_tree(const vector<vector<double>> &X, const vector<int> &y, int depth, int max_depth);
    int best_split(const vector<vector<double>> &X, const vector<int> &y, double &threshold);
};