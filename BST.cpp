#include "BST.h"

BST::~BST() {
    if (val != 0) {
        delete this->left;
        delete this->right;
    }
};

void BST::addNode(char key) {
    if (val == 0) {
        this->val = key;
        this->left = new BST();
        this->right = new BST();
    } else {
        if (key < this->val) {
            this->left->addNode(key);
        } else {
            this->right->addNode(key);
        }
    }
};

void BST::addNodes(char* key, int n) {
    for (int i = 0; i < n; i++)
        addNode(key[i]);
};

int BST::simulateSearchNode(char key) {
    if (key == this->val)
        return 1;
    if (key < this->val)
        return 1 + this->left->simulateSearchNode(key);
    else    
        return 1 + this->right->simulateSearchNode(key);
};

int BST::simulateSearchNodes(char* key, float* prob, int n) {
    int sum = 0;
    for (int i = 0; i < n; i++)
        sum += 1000*prob[i]*simulateSearchNode(key[i]);
    return sum;
};

void BST::printBT(int spacing) {
    if (this->val == 0)
        return;
    this->right->printBT(spacing+10);
    cout << string(spacing, ' ') << this->val << endl;
    this->left->printBT(spacing+10);
};