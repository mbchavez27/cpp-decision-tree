#pragma once
#include <vector>

struct Node
{
    int feature_index;
    double threshold;
    Node *left;
    Node *right;
    bool is_leaf;
    int label;

    Node() : feature_index(-1), threshold(0.0), left(nullptr), right(nullptr), is_leaf(false), label(-1) {}
}