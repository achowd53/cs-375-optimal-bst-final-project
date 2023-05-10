#include "oBST.h"
#include <queue>
#include <tuple>
#include <set>
#include <algorithm>

oBST::~oBST() {
    if (val != 0) {
        delete this->left;
        delete this->right;
    }
};

void oBST::sort_keys(int n, char* key, float* prob) {
    pair<char, float> pairs[n];

    for (int i = 0; i < n; i++) pairs[i] = make_pair(key[i], prob[i]);

    std::sort( pairs, pairs+n, [](auto &left, auto &right) {
        return left.first < right.first;
    });

    for (int i = 0; i < n; i++) {
        key[i] = pairs[i].first;
        prob[i] = pairs[i].second;
    }
}

void oBST::optimize(int n, char* key, float* prob, char* optimized_order) {
    sort_keys(n, key, prob); // sort keys in lexicographic order, make sure probs are in corresponding order
    float cost[n][n]; // keep track of optimal cost
    int idxs[n][n][4]; // keep track of what subtrees were used for calculation
    int root[n][n]; // keep track of the root of a certain subtree

    for (int a = 0; a < n; a++) { // fill all these matrices with zeros
        for (int b = 0; b < n; b++) {
            cost[a][b] = 0.0;
            if (a == b) cost[a][b] = prob[a];
            root[a][b] = 0;
            for (int c = 0; c < 4; c++) {
                idxs[a][b][c] = 0;
            }
        }
    }

    for (int l = 2; l <= n; l++) { // go along diagonally across the cost matrices to calculate optimal cost
        for (int i = 0; i <= n-l+1; i++) {
            int j = i+l-1;
            if (j >= n) continue; // make sure we don't access outside the matrix
            int subroot = 0;
            cost[i][j] = 100.0; // keep track of the lowest cost for a subtree
            float sum = 0;
            for (int k = i; k <= j; k++) sum += prob[k];
            for (int r = i; r <= j; r++) {
                float c = ((r > i)? cost[i][r-1]:0) + ((r < j)? cost[r+1][j]:0) + sum;
                if (c <= cost[i][j]) {
                    cost[i][j] = c; // get the lowest cost
                    idxs[i][j][0] = i; // these next 4 lines just keep track of the idxs of the two subtrees
                    idxs[i][j][1] = r-1;
                    idxs[i][j][2] = r+1;
                    idxs[i][j][3] = j;
                    root[i][j] = r; // keep track of the root idx used for the root of the subtree
                }
            } 
        }
    }

    // cout << cost[0][n-1] << endl; // print optimal cost
    
    queue<tuple<int, int>> child; // similar to bfs, go backwards to fill in the construction of the oBST
    int i = 0;
    set<int> nums; // make sure we only have unique idxs added to the tree
    for (int x = 0; x < n; x++) nums.insert(x);
    nums.erase(root[0][n-1]);

    optimized_order[i] = key[root[0][n-1]];
    child.push(tuple<int, int>{idxs[0][n-1][0], idxs[0][n-1][1]}); // push left child
    child.push(tuple<int, int>{idxs[0][n-1][2], idxs[0][n-1][3]}); // push right child

    i++;
    while (!child.empty() && i < n) {
        tuple<int, int> curr = child.front(); // check front of the queue
        child.pop();
        int root_idx = root[get<0>(curr)][get<1>(curr)];
        if (cost[get<0>(curr)][get<1>(curr)] == 0.0) continue; // if cost of this node is 0, then skip
        if (nums.count(root_idx) == 1) { // make sure it's a unique root idx
            nums.erase(root_idx);
        } else {
            int setint = *nums.begin();
            root_idx = setint;
            nums.erase(setint);
        }
        optimized_order[i] = key[root_idx]; // add to the optimized order of the nodes
        i++;
        if (root_idx != 0) { // as long as it's not a leaf node, add it's left and right children
            child.push(tuple<int, int>{idxs[get<0>(curr)][get<1>(curr)][0], idxs[get<0>(curr)][get<1>(curr)][1]});
            child.push(tuple<int, int>{idxs[get<0>(curr)][get<1>(curr)][2], idxs[get<0>(curr)][get<1>(curr)][3]});
        }
    }
}

void oBST::addNode(char key) {
    if (val == 0) {
        this->val = key;
        this->left = new oBST();
        this->right = new oBST();
    } else {
        if (key < this->val) {
            this->left->addNode(key);
        } else {
            this->right->addNode(key);
        }
    }
};

void oBST::addNodes(char* key, float* prob, int n) {
    char* optimized_order = new char[n];
    optimize(n, key, prob, optimized_order);
    for (int i = 0; i < n; i++) {
        addNode(optimized_order[i]);
    }
};

int oBST::simulateSearchNode(char key) {
    if (key == this->val)
        // cout << "found: " << key << endl;
        return 1;
    if (key < this->val)
        return 1 + this->left->simulateSearchNode(key);
    else    
        return 1 + this->right->simulateSearchNode(key);
};

int oBST::simulateSearchNodes(char* key, float* prob, int n) {
    int sum = 0;
    for (int i = 0; i < n; i++) {
        // cout << "find: " << key[i] << endl;
        sum += 1000*prob[i]*simulateSearchNode(key[i]);
    } return sum;
};

void oBST::printBT(int spacing) {
    if (this->val == 0)
        return;
    this->right->printBT(spacing+10);
    cout << string(spacing, ' ') << this->val << endl;
    this->left->printBT(spacing+10);
};