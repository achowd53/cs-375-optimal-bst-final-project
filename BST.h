#include <iostream>
#include <string>
using namespace std;

class BST {
    public:
        BST() {
            left = nullptr;
            right = nullptr;
            val = 0;
        }
        ~BST();
        BST *left;
        BST *right;
        char val;
        void addNode(char key);
        void addNodes(char* key, int n);
        int simulateSearchNode(char key);
        int simulateSearchNodes(char* key, float* prob, int n);
        void printBT(int spacing);
};