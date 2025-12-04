#pragma once
#include <vector>
using namespace std;

double gini_impurity(const vector<int> &y);
double gini_split(const vector<int> &left_y, const vector<int> &right_y);

double variance(const vector<int> &y);
